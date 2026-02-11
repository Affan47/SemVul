finished_time_slice(ACTIVE_TASK* atp) {
    double time_slice_end = atp->run_interval_start_wall_time + gstate.global_prefs.cpu_scheduling_period();
    bool running_beyond_sched_period = gstate.now > time_slice_end;
    bool checkpointed = atp->checkpoint_wall_time > time_slice_end;
    if (running_beyond_sched_period && !checkpointed) {
        atp->overdue_checkpoint = true;
    }
    return (running_beyond_sched_period && checkpointed);
}
