rewriteConfigStringOption(struct rewriteConfigState *state, char *option, char *value, char *defvalue) {
    int force = 1;
    sds line;


    if (value == NULL) {
        rewriteConfigMarkAsProcessed(state,option);
        return;
    }


    if (defvalue && strcmp(value,defvalue) == 0) force = 0;

    line = sdsnew(option);
    line = sdscatlen(line, " ", 1);
    line = sdscatrepr(line, value, strlen(value));

    rewriteConfigRewriteLine(state,option,line,force);
}
