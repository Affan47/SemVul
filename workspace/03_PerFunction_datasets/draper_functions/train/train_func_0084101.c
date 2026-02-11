handle_result_op(GUI_RPC_CONN& grc, const char* op) {
    RESULT* rp;
    char result_name[256];
    ACTIVE_TASK* atp;
    string project_url;

    strcpy(result_name, "");
    while (!grc.xp.get_tag()) {
        if (grc.xp.parse_str("name", result_name, sizeof(result_name))) continue;
        if (grc.xp.parse_string("project_url", project_url)) continue;
    }
    PROJECT* p = get_project(grc, project_url);
    if (!p) return;

    if (!strlen(result_name)) {
        grc.mfout.printf("<error>Missing result name</error>\n");
        return;
    }

    rp = gstate.lookup_result(p, result_name);
    if (!rp) {
        grc.mfout.printf("<error>no such result</error>\n");
        return;
    }

    if (!strcmp(op, "abort")) {
        msg_printf(p, MSG_INFO, "task %s aborted by user", result_name);
        atp = gstate.lookup_active_task_by_result(rp);
        if (atp) {
            atp->abort_task(EXIT_ABORTED_VIA_GUI, "aborted by user");
        } else {
            rp->abort_inactive(EXIT_ABORTED_VIA_GUI);
        }
        gstate.request_work_fetch("result aborted by user");
    } else if (!strcmp(op, "suspend")) {
        msg_printf(p, MSG_INFO, "task %s suspended by user", result_name);
        rp->suspended_via_gui = true;
        gstate.request_work_fetch("task suspended by user");
    } else if (!strcmp(op, "resume")) {
        msg_printf(p, MSG_INFO, "task %s resumed by user", result_name);
        rp->suspended_via_gui = false;
    }
    gstate.request_schedule_cpus("task suspended, resumed or aborted by user");
    gstate.set_client_state_dirty("Result RPC");
    grc.mfout.printf("<success/>\n");
}
