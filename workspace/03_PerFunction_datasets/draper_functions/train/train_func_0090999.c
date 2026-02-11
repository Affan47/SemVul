work_needed(bool locality_sched) {
    if (locality_sched) {


        if (g_wreq->disk.insufficient || g_wreq->speed.insufficient || g_wreq->mem.insufficient || g_wreq->no_allowed_apps_available) {
            if (config.debug_send) {
                log_messages.printf(MSG_NORMAL,
                    "[send] stopping work search - locality condition\n"
                );
            }
            return false;
        }
    }


    bool some_type_allowed = false;


    if (config.max_jobs_in_progress.exceeded(NULL, true)) {
        if (config.debug_quota) {
            log_messages.printf(MSG_NORMAL,
                "[quota] reached limit on GPU jobs in progress\n"
            );
            config.max_jobs_in_progress.print_log();
        }
        g_wreq->clear_gpu_req();
        if (g_wreq->effective_ngpus) {
            g_wreq->max_jobs_on_host_gpu_exceeded = true;
        }
    } else {
        some_type_allowed = true;
    }


    if (config.max_jobs_in_progress.exceeded(NULL, false)) {
        if (config.debug_quota) {
            log_messages.printf(MSG_NORMAL,
                "[quota] reached limit on CPU jobs in progress\n"
            );
            config.max_jobs_in_progress.print_log();
        }
        g_wreq->clear_cpu_req();
        g_wreq->max_jobs_on_host_cpu_exceeded = true;
    } else {
        some_type_allowed = true;
    }

    if (!some_type_allowed) {
        if (config.debug_send) {
            log_messages.printf(MSG_NORMAL,
                "[send] in-progress job limit exceeded\n"
            );
        }
        g_wreq->max_jobs_on_host_exceeded = true;
        return false;
    }


    if (g_wreq->njobs_sent >= g_wreq->max_jobs_per_rpc) {
        if (config.debug_quota) {
            log_messages.printf(MSG_NORMAL,
                "[quota] stopping work search - njobs %d >= max_jobs_per_rpc %d\n",
                g_wreq->njobs_sent, g_wreq->max_jobs_per_rpc
            );
        }
        return false;
    }

#if 0
    if (config.debug_send) {
        char buf[256], buf2[256];
        strcpy(buf, "");
        for (int i=1; i<NPROC_TYPES; i++) {
            sprintf(buf2, " %s (%.2f, %.2f)",
                proc_type_name(i),
                g_wreq->req_secs[i],
                g_wreq->req_instances[i]
            );
            strcat(buf, buf2);
        }
        log_messages.printf(MSG_NORMAL,
            "[send] work_needed: spec req %d sec to fill %.2f; %s\n",
            g_wreq->rsc_spec_request,
            g_wreq->seconds_to_fill,
            buf
        );
    }
#endif
    if (g_wreq->rsc_spec_request) {
        for (int i=0; i<NPROC_TYPES; i++) {
            if (g_wreq->need_proc_type(i) && have_apps(i)) {
                return true;
            }
        }
    } else {
        if (g_wreq->seconds_to_fill > 0) {
            return true;
        }
    }
    if (config.debug_send) {
        log_messages.printf(MSG_NORMAL, "[send] don't need more work\n");
    }
    return false;
}
