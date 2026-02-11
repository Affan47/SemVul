history_find(char *cmd)
{
    int len;


    if (*cmd == '"') cmd++;
    if (!*cmd) return 0;
    len = strlen(cmd);
    if (cmd[len - 1] == '"') cmd[--len] = 0;
    if (!*cmd) return 0;


    if (history_search_prefix(cmd, -1) == 0)
        return current_history()->line;
    return NULL;
}
