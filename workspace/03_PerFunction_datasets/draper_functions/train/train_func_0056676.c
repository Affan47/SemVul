fsdb_init_file_info(fsdb_file_info *info) {
    info->days = 0;
    info->mins = 0;
    info->ticks = 0;
    info->comment = NULL;
    info->mode = A_FIBF_READ | A_FIBF_WRITE | A_FIBF_EXECUTE | A_FIBF_DELETE;

    if (uae_deterministic_mode()) {

    }
    else {
        fs_time_val tv;
        fs_get_current_time(&tv);
        struct mytimeval mtv;
        mtv.tv_sec = tv.tv_sec + fs_get_local_time_offset(tv.tv_sec);
        mtv.tv_usec = tv.tv_usec;
        timeval_to_amiga (&mtv, &info->days, &info->mins, &info->ticks);
        if (g_fsdb_debug) {
            write_log("- initialized date/time from current time\n");
            write_log("- days %d mins %d ticks %d - %lld %d\n",
                    info->days, info->mins, info->ticks, mtv.tv_sec,
                    mtv.tv_usec);
        }
    }
}
