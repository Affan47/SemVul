do_generate() {
    FE.prepare_proc_iteration();
    ast_procdef* proc = FE.get_next_proc();


    char* proc_name = proc->get_procname()->get_genname();
    if (strcmp(proc_name, fname) != 0) {
        gm_backend_error(GM_ERROR_GPS_PROC_NAME, proc->get_procname()->get_genname(), fname);
        return false;
    }

    if (!open_output_files()) return false;

    bool b = gm_apply_compiler_stage(get_gen_steps());

    close_output_files();

    return b;
}
