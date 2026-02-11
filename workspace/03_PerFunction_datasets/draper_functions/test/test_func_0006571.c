linenoiseHistoryAdd(char *line) {
    if (history_max_len == 0) return 0;
    if (history == 0) {
        history = malloc(sizeof(char*)*history_max_len);
        if (history == NULL) return 0;
        memset(history,0,(sizeof(char*)*history_max_len));
    }
    line = strdup(line);
    if (!line) return 0;
    if (history_len == history_max_len) {
        memmove(history,history+1,sizeof(char*)*(history_max_len-1));
        history_len--;
    }
    history[history_len] = line;
    history_len++;
    return 1;
}
