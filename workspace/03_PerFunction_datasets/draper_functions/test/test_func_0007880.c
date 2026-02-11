stop_operation(bool drain)
{

  DBC_REQUIRE(is_prepared() == true);


  ECA_LOG_MSG(ECA_LOGGER::system_objects, "stopping engine operation!");


  for (unsigned int adev_sizet = 0; adev_sizet != realtime_objects_rep.size(); adev_sizet++) {
    if (realtime_objects_rep[adev_sizet]->is_running() == true)
      realtime_objects_rep[adev_sizet]->stop(drain);
  }

  prepared_rep = false;


  for(size_t n = 0; n < cslots_rep.size(); n++) {
    cslots_rep[n]->set_rt_lock(false);
  }
  mixslot_repp->set_rt_lock(false);

  stop_servers();
  stop_forked_objects();


  if (csetup_repp->raised_priority() == true) {
    if (kvu_set_thread_scheduling(SCHED_OTHER, 0) != 0)
      ECA_LOG_MSG(ECA_LOGGER::info, "Unable to change scheduling back to SCHED_OTHER!");
    else
      ECA_LOG_MSG(ECA_LOGGER::system_objects, "Changed back to non-realtime scheduling SCHED_OTHER.");
  }


  csetup_repp->toggle_locked_state(false);


  signal_stop();


  DBC_ENSURE(is_running() != true);
  DBC_ENSURE(is_prepared() != true);

}
