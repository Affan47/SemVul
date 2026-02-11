write_gui(MIOFILE& fout) {


    double fd = fraction_done;
    if (fd == 0 && elapsed_time > 0) {
        double est_time = wup->rsc_fpops_est/app_version->flops;
        double x = elapsed_time/est_time;
		fd = 1 - exp(-x);
    }
    fout.printf(
        "<active_task>\n"
        "    <active_task_state>%d</active_task_state>\n"
        "    <app_version_num>%d</app_version_num>\n"
        "    <slot>%d</slot>\n"
        "    <pid>%d</pid>\n"
        "    <scheduler_state>%d</scheduler_state>\n"
        "    <checkpoint_cpu_time>%f</checkpoint_cpu_time>\n"
        "    <fraction_done>%f</fraction_done>\n"
        "    <current_cpu_time>%f</current_cpu_time>\n"
        "    <elapsed_time>%f</elapsed_time>\n"
        "    <swap_size>%f</swap_size>\n"
        "    <working_set_size>%f</working_set_size>\n"
        "    <working_set_size_smoothed>%f</working_set_size_smoothed>\n"
        "    <page_fault_rate>%f</page_fault_rate>\n"
        "%s"
        "%s",
        task_state(),
        app_version->version_num,
        slot,
        pid,
        scheduler_state,
        checkpoint_cpu_time,
        fd,
        current_cpu_time,
        elapsed_time,
        procinfo.swap_size,
        procinfo.working_set_size,
        procinfo.working_set_size_smoothed,
        procinfo.page_fault_rate,
        too_large?"   <too_large/>\n":"",
        needs_shmem?"   <needs_shmem/>\n":""
    );
    if (strlen(app_version->graphics_exec_path)) {
        fout.printf(
            "   <graphics_exec_path>%s</graphics_exec_path>\n"
            "   <slot_path>%s</slot_path>\n",
            app_version->graphics_exec_path,
            slot_path
        );
    }
    if (strlen(web_graphics_url)) {
        fout.printf(
            "   <web_graphics_url>%s</web_graphics_url>\n",
            web_graphics_url
        );
    }
    if (strlen(remote_desktop_addr)) {
        fout.printf(
            "   <remote_desktop_addr>%s</remote_desktop_addr>\n",
            remote_desktop_addr
        );
    }
    fout.printf("</active_task>\n");
    return 0;
}
