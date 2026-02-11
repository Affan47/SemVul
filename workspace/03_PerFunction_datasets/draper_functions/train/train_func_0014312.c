init_history(void) {
    using_history();
    char *home = getenv("HOME");
    if (!home) return;
    asprintf(&history_file, "%s/.julia_history", home);
    struct stat stat_info;
    if (!stat(history_file, &stat_info)) {
        read_history(history_file);
        for (;;) {
            HIST_ENTRY *entry = history_get(history_base);
            if (entry && isspace(entry->line[0]))
                free_history_entry(history_rem(history_base));
            else break;
        }
        int i, j, k;
        for (i=1 ;; i++) {
            HIST_ENTRY *first = history_get(i);
            if (!first) break;
            int length = strlen(first->line)+1;
            for (j = i+1 ;; j++) {
                HIST_ENTRY *child = history_get(j);
                if (!child || !isspace(child->line[0])) break;
                length += strlen(child->line)+1;
            }
            if (j == i+1) continue;
            first->line = (char*)realloc(first->line, length);
            char *p = strchr(first->line, '\0');
            for (k = i+1; k < j; k++) {
                *p = '\n';
                p = stpcpy(p+1, history_get(i+1)->line);
                free_history_entry(history_rem(i+1));
            }
        }
    } else if (errno == ENOENT) {
        write_history(history_file);
    } else {
        ios_printf(ios_stderr, "history file error: %s\n", strerror(errno));
        exit(1);
    }
}
