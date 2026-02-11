get_disk_shares() {
    PROJECT* p;
    unsigned int i;


    double trs = 0;
    double max_rs = 0;
    for (i=0; i<projects.size(); i++) {
        p = projects[i];
        p->ddu = std::max(p->disk_usage, p->desired_disk_usage);
        double rs = p->resource_share;
        trs += rs;
        if (rs > max_rs) max_rs = rs;
    }
    if (trs) {
        max_rs /= 10;
        for (i=0; i<projects.size(); i++) {
            p = projects[i];
            p->disk_resource_share = p->resource_share + max_rs;
        }
    } else {
        for (i=0; i<projects.size(); i++) {
            p = projects[i];
            p->disk_resource_share = 1;
        }
    }


    double greedy_drs = 0;
    double non_greedy_ddu = 0;
    double allowed = allowed_disk_usage(total_disk_usage);
    for (i=0; i<projects.size(); i++) {
        p = projects[i];
        p->disk_quota = allowed*p->disk_resource_share/trs;
        if (p->ddu > p->disk_quota) {
            greedy_drs += p->disk_resource_share;
        } else {
            non_greedy_ddu += p->ddu;
        }
    }

    double greedy_allowed = allowed - non_greedy_ddu;
    if (log_flags.disk_usage_debug) {
        msg_printf(0, MSG_INFO,
            "[disk_usage] allowed %.2fMB used %.2fMB",
            allowed/MEGA, total_disk_usage/MEGA
        );
    }
    for (i=0; i<projects.size(); i++) {
        p = projects[i];
        double rs = p->disk_resource_share/trs;
        if (p->ddu > allowed*rs) {
            p->disk_share = greedy_allowed*p->disk_resource_share/greedy_drs;
        } else {
            p->disk_share = p->disk_quota;
        }
        if (log_flags.disk_usage_debug) {
            msg_printf(p, MSG_INFO,
                "[disk_usage] usage %.2fMB share %.2fMB",
                p->disk_usage/MEGA, p->disk_share/MEGA
            );
        }
    }
}
