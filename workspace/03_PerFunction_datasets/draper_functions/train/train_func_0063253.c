check_files(char** infiles, int ninfiles, SCHED_CONFIG& config_loc) {
    int i;
    char path[MAXPATHLEN];

    for (i=0; i<ninfiles; i++) {
        dir_hier_path(
            infiles[i], config_loc.download_dir, config_loc.uldl_dir_fanout, path
        );
        if (!boinc_file_exists(path)) {
            return 1;
        }

    }
    return 0;
}
