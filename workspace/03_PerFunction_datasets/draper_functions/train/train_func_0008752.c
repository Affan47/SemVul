execute()
{
  omniORB::logs(25, "Scavenger task execute.");

  unsigned long abs_sec,abs_nsec;
  omni_thread::get_time(&abs_sec,&abs_nsec);

  while (1) {
    {
      omni_tracedmutex_lock sync(*mutex);
      if ( shutdown || !orbParameters::scanGranularity ) {
	goto died;
      }
      omni_thread::get_time(&abs_sec,&abs_nsec,orbParameters::scanGranularity);
      cond->timedwait(abs_sec,abs_nsec);
    }

    if (omniORB::trace(30)) {
      omniORB::logger log;
      log << "Scan for idle connections ("
	  << abs_sec << "," << abs_nsec << ")\n";
    }

    StrandList client_shutdown_list;
    StrandList server_shutdown_list;
    {


      omni_tracedmutex_lock sync(*omniTransportLock);


      removeIdle(giopStrand::active_timedout,client_shutdown_list,1);
      removeIdle(giopStrand::active,client_shutdown_list,1);
      removeIdle(giopStrand::passive,server_shutdown_list,0);
    }


    {
      StrandList* p = client_shutdown_list.next;
      while ( p != &client_shutdown_list ) {
	giopStrand* s = (giopStrand*)p;
	p = p->next;
	s->StrandList::remove();
	s->state(giopStrand::DYING);
        if ( s->version.minor >= 2 && s->connection ) {


          sendCloseConnection(s);
        }
	s->safeDelete(1);
      }
    }

    {


      omni_tracedmutex_lock sync(*omniTransportLock);

      StrandList* p = server_shutdown_list.next;
      while ( p != &server_shutdown_list ) {
	giopStrand* s = (giopStrand*)p;
	p = p->next;
	s->StrandList::remove();
	s->state(giopStrand::DYING);
	sendCloseConnection(s);
	s->connection->Shutdown();
      }
    }

    if (omniORB::trace(30)) {
      omniORB::logger log;
      log << "Scan for idle connections done ("
	  << abs_sec << "," << abs_nsec << ").\n";
    }
  }

 died:
  {
    mutex->lock();
    theTask = 0;
    if (shutdown) {
      mutex->unlock();
      delete cond;
      delete mutex;
    }
    else {
      mutex->unlock();
    }
    delete this;
  }
}
