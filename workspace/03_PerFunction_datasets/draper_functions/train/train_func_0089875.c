perform(unsigned long secs, unsigned long nanosecs)
{
  orb_lock.lock();
  invoker_threads++;

  while (!invoker_shutting_down) {

    while (!invoker_shutting_down &&
	   omniTaskLink::is_empty(invoker_dedicated_tq)) {


      if (secs || nanosecs) {
	if (invoker_signal.timedwait(secs, nanosecs) == 0) {

	  invoker_threads--;
	  if (invoker_shutting_down) invoker_signal.signal();
	  orb_lock.unlock();
	  return;
	}
      }
      else {
	invoker_signal.wait();
      }
    }
    while (!omniTaskLink::is_empty(invoker_dedicated_tq)) {

      omniTask* t = (omniTask*)invoker_dedicated_tq.next;
      t->deq();
      orb_lock.unlock();
      try {
	t->execute();
      }
      catch (...) {
	omniORB::logs(1, "ORBAsyncInvoker: Warning - unexpected "
		      "exception caught while executing a task.");
      }
      orb_lock.lock();
    }
  }
  OMNIORB_ASSERT(omniTaskLink::is_empty(invoker_dedicated_tq));

  invoker_threads--;
  if (invoker_shutting_down) invoker_signal.signal();
  orb_lock.unlock();
}
