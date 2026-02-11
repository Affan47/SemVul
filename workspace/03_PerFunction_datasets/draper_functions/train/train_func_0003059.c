tools_sync_script(iTunesDB *itdb, SyncType type) {
    gchar *script = NULL;
    gchar *script_path, *buf;
    gchar **argv = NULL;
    GString *script_output;
    gint fdpipe[2];
    gint len;
    pid_t pid;

    switch (type) {
    case SYNC_CONTACTS:
        script = get_itdb_prefs_string(itdb, "path_sync_contacts");
        break;
    case SYNC_CALENDAR:
        script = get_itdb_prefs_string(itdb, "path_sync_calendar");
        break;
    case SYNC_NOTES:
        script = get_itdb_prefs_string(itdb, "path_sync_notes");
        break;
    default:
        fprintf(stderr, "Programming error: tools_sync_script () called with %d\n", type);
        return FALSE;
    }


    if (script)
        g_strstrip(script);

    if (!script || (strlen(script) == 0)) {
        gtkpod_warning(_("Please specify the command to be called on the 'Tools' section of the preferences dialog.\n"));
        g_free(script);
        return FALSE;
    }

    argv = g_strsplit(script, " ", -1);

    tools_sync_replace_percent_i(itdb, argv);

    script_path = g_find_program_in_path(argv[0]);
    if (!script_path) {
        gtkpod_warning(_("Could not find the command '%s'.\n\nPlease verify the setting in the 'Tools' section of the preferences dialog.\n\n"), argv[0]);
        g_free(script);
        g_strfreev(argv);
        return FALSE;
    }


    g_free(argv[0]);
    argv[0] = g_path_get_basename(script_path);

    buf = g_malloc(BUFLEN);
    script_output = g_string_sized_new(BUFLEN);


    pipe(fdpipe);

    pid = fork();


    switch (pid) {
    case -1:
        break;
    case 0:
        close(fdpipe[READ]);
        dup2(fdpipe[WRITE], fileno(stdout));
        dup2(fdpipe[WRITE], fileno(stderr));
        close(fdpipe[WRITE]);
        execv(script_path, argv);
        break;
    default:
        close(fdpipe[WRITE]);
        waitpid(pid, NULL, 0);
        do {
            len = read(fdpipe[READ], buf, BUFLEN);
            if (len > 0)
                g_string_append_len(script_output, buf, len);
        }
        while (len > 0);
        close(fdpipe[READ]);

        if (strlen(script_output->str)) {
            gtkpod_warning(_("'%s' returned the following output:\n%s\n"), script_path, script_output->str);
        }
        break;
    }


    g_free(script_path);
    g_free(buf);
    g_strfreev(argv);
    g_string_free(script_output, TRUE);
    return TRUE;
}
