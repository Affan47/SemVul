rewriteConfigBindOption(struct rewriteConfigState *state) {
    int force = 1;
    sds line, addresses;
    char *option = "bind";


    if (server.bindaddr_count == 0) {
        rewriteConfigMarkAsProcessed(state,option);
        return;
    }


    addresses = sdsjoin(server.bindaddr,server.bindaddr_count," ");
    line = sdsnew(option);
    line = sdscatlen(line, " ", 1);
    line = sdscatsds(line, addresses);
    sdsfree(addresses);

    rewriteConfigRewriteLine(state,option,line,force);
}
