check_save_state(int slot) {
    char *title = NULL;
    char *state_file = get_state_file(slot, "uss");
    fs_emu_log("check %s\n", state_file);
    if (fs_path_exists(state_file)) {
        fs_emu_log("exists\n");
        struct fs_stat buf;
        if (fs_stat(state_file, &buf) == 0) {


            struct tm tm_struct;
            fs_localtime_r(&buf.mtime, &tm_struct);
            char strbuf[32];

            strftime(strbuf, 32, "%Y-%m-%d %H:%M:%S", &tm_struct);

            title = fs_strdup(strbuf);
        }
    }
    free(state_file);
    return title;
}
