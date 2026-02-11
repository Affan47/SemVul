send_heartbeats() {
    unsigned int i;
    ACTIVE_TASK* atp;
    char buf[1024];
    double ar = gstate.available_ram();

    for (i=0; i<active_tasks.size(); i++) {
        atp = active_tasks[i];
        if (!atp->process_exists()) continue;
        if (!atp->app_client_shm.shm) continue;
        snprintf(buf, sizeof(buf), "<heartbeat/>"
            "<wss>%e</wss>"
            "<max_wss>%e</max_wss>",
            atp->procinfo.working_set_size, ar
        );
        if (gstate.network_suspended) {
            strcat(buf, "<network_suspended/>");
        }
        bool sent = atp->app_client_shm.shm->heartbeat.send_msg(buf);
        if (log_flags.heartbeat_debug) {
            if (sent) {
                msg_printf(atp->result->project, MSG_INFO,
                    "[heartbeat] Heartbeat sent to task %s",
                    atp->result->name
                );
            } else {
                msg_printf(atp->result->project, MSG_INFO,
                    "[heartbeat] Heartbeat to task %s failed, previous message unread",
                    atp->result->name
                );
            }
        }
    }
}
