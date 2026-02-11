process_control_poll() {
    unsigned int i;
    ACTIVE_TASK* atp;

    for (i=0; i<active_tasks.size(); i++) {
        atp = active_tasks[i];
        if (!atp->process_exists()) continue;
        if (!atp->app_client_shm.shm) continue;


        if (atp->process_control_queue.timeout(180)) {
            if (log_flags.task_debug) {
                msg_printf(atp->result->project, MSG_INFO,
                    "Restarting %s - message timeout", atp->result->name
                );
            }
            atp->kill_task(true);
        } else {
            atp->process_control_queue.msg_queue_poll(
                atp->app_client_shm.shm->process_control_request
            );
        }
    }
}
