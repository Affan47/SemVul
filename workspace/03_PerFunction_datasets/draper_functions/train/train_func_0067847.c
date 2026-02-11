notifyRzNewConnection(giopRendezvouser* r, giopConnection* conn)
{
  omni_tracedmutex_lock sync(pd_lock);

  switch (pd_state) {
  case ACTIVE:
    {
      connectionState* cs = csInsert(conn);

      if (conn->pd_has_dedicated_thread) {
	giopWorker* task = new giopWorker(cs->strand, this, 0);
	if (!orbAsyncInvoker->insert(task)) {

	  if (omniORB::trace(1)) {
	    omniORB::logger log;
	    log << "Cannot create a worker for this endpoint: "
		<< conn->myaddress()
		<< " from "
		<< conn->peeraddress()
		<< "\n";
	  }
	  delete task;
	  {
	    omni_tracedmutex_lock sync(*omniTransportLock);
	    cs->strand->safeDelete();
	  }
	  csRemove(conn);
	  pd_lock.unlock();
	  delete cs;
	  pd_lock.lock();

	  throw outOfResource();
	}
	task->insert(cs->workers);
	conn->pd_n_workers++;
	pd_n_dedicated_workers++;
      }
      else {
	if (!conn->isSelectable()) {
	  if (omniORB::trace(20)) {
	    omniORB::logger log;
	    log << "Connection from " << conn->peeraddress()
		<< " is not selectable. Closing it.\n";
	  }
	  {
	    omni_tracedmutex_lock sync(*omniTransportLock);
	    cs->strand->safeDelete();
	  }
	  csRemove(conn);
	  pd_lock.unlock();
	  delete cs;
	  pd_lock.lock();
	  throw outOfResource();
	}
	pd_lock.unlock();
	conn->setSelectable(1);
	pd_lock.lock();
      }
      break;
    }
  default:
    if (omniORB::trace(25)) {
      omniORB::logger l;
      l << "giopServer terminate connection from "
	<< conn->peeraddress() << ".\n";
    }
    throw Terminate();
  }
}
