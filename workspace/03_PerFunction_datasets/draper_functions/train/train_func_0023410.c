sufficient_coprocs(RESULT& r) {
        double x;
        APP_VERSION& av = *r.avp;
        int rt = av.gpu_usage.rsc_type;
        if (!rt) return true;
        x = av.gpu_usage.usage;
        COPROC& cp = pr_coprocs.coprocs[rt];
        for (int i=0; i<cp.count; i++) {
            if (gpu_excluded(r.app, cp, i)) continue;
            if (cp.usage[i]+x <=1) return true;
        }
        if (log_flags.cpu_sched_debug) {
            msg_printf(r.project, MSG_INFO,
                "[cpu_sched_debug] insufficient %s for %s",
                cp.type, r.name
            );
        }
        return false;
    }
