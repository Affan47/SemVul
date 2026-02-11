command_table_get_label_array (InputPadTableCmd *cmds)
{
    int i = 0, len;
    char **retval = NULL;

    if (cmds == NULL) {
        return NULL;
    }
    while (cmds[i].execl) {
        i++;
    }
    len = i;
    retval = g_new0 (char *, len + 1);
    for (i = 0; cmds[i].execl; i++) {
        if (cmds[i].label) {
            retval[i] = g_strdup (cmds[i].label);
        } else {
            retval[i] = g_strdup (cmds[i].execl);
        }
    }

    return retval;
}
