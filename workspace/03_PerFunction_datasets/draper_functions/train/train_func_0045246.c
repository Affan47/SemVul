ns_screen_xcommand(_ns_sess * s, char prefix, char *cmd)
{
    char *i;
    int ret = NS_OOM;

    if ((i = MALLOC(strlen(cmd) + 4))) {
        size_t l = strlen(cmd) + 2;

        strcpy(&i[2], cmd);
        i[0] = s->escape;
        i[1] = prefix;
        i[l] = '\n';
        i[++l] = '\0';
        ret = ns_screen_command(s, i);
        FREE(i);
    }
    D_ESCREEN(("Returning %d\n", ret));
    return ret;
}
