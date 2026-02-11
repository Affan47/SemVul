removeConnectionAndWorker(giopWorker* w)
{
  ASSERT_OMNI_TRACEDMUTEX_HELD(pd_lock, 0);

  connectionState* cs;
  CORBA::Boolean   cs_removed = 0;

  {
    omni_tracedmutex_lock sync(pd_lock);

    giopConnection* conn = w->strand()->connection;

    conn->pd_dying = 1;


    cs = csLocate(conn);


    pd_lock.unlock();

    conn->clearSelectable();


    pd_lock.lock();

    int workers;
    CORBA::Boolean singleshot = w->singleshot();

    if (singleshot)
      workers = --pd_n_temporary_workers;
    else
      workers = --pd_n_dedicated_workers;

    w->remove();
    delete w;

    conn->pd_n_workers--;

    if (Link::is_empty(cs->workers)) {
      csRemove(conn);
      cs_removed = 1;
    }

    if (pd_state == INFLUX) {
      if (omniORB::trace(25)) {
	omniORB::logger l;
	l << "removeConnectionAndWorker for "
	  << (singleshot ? "temporary" : "dedicated")
	  << " worker. " << workers << " remaining.\n";
      }
      if (workers == 0) {
	pd_cond.broadcast();
      }
    }
  }


  if (cs_removed)
    delete cs;
}
