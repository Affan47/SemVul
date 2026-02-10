notifyMrDone(giopMonitor* m, CORBA::Boolean exit_on_error)
{
  ASSERT_OMNI_TRACEDMUTEX_HELD(pd_lock,0);
  omni_tracedmutex_lock sync(pd_lock);

  if (!exit_on_error && !m->collection()->isEmpty()) {


    if (orbAsyncInvoker->insert(m)) {
      return;
    }

  }
  m->remove();
  delete m;
  if (pd_state == INFLUX) {
    if (Link::is_empty(pd_bidir_monitors)) {
      omniORB::logs(25, "No remaining bidir monitors.");
      pd_cond.broadcast();
    }
  }
}
