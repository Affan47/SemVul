cmd_tcf(char *s) {
    int i;
    int ind;
    char * args[maxargs];
    Channel * c = chan;

    if (c == NULL) {
        printf("Error: Channel not connected, use 'connect' command\n");
        return 0;
    }
    ind = 0;
    args[ind] = strtok(s, " \t");
    while (args[ind] != NULL && ++ind < maxargs) {
        args[ind] = strtok(NULL, " \t");
    }
    if (args[0] == NULL || args[1] == NULL) {
        printf("Error: Expected at least service and command name arguments\n");
        return 0;
    }
    protocol_send_command(c, args[0], args[1], display_tcf_reply, c);
    for (i = 2; i < ind; i++) {
        write_stringz(&c->out, args[i]);
    }
    write_stream(&c->out, MARKER_EOM);
    return 1;
}
