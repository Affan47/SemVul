log_reopen(void)
{
    int i, j, found;


    gw_rwlock_wrlock(&rwlock);

    for (i = 0; i < num_logfiles; ++i) {
        if (logfiles[i].file != stderr) {
            found = 0;


            for (j = i-1; j >= 0 && found == 0; j--) {
                if (strcmp(logfiles[i].filename, logfiles[j].filename) == 0) {
                    logfiles[i].file = logfiles[j].file;
                    found = 1;
                }
            }
            if (found)
                continue;
            if (logfiles[i].file != NULL)
                fclose(logfiles[i].file);
            logfiles[i].file = fopen(logfiles[i].filename, "a");
            if (logfiles[i].file == NULL) {
                error(errno, "Couldn't re-open logfile `%s'.",
                      logfiles[i].filename);
            }
        }
    }


    gw_rwlock_unlock(&rwlock);
}
