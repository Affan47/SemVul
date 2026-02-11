getKeysFromCommand(struct redisCommand *cmd,robj **argv, int argc, int *numkeys, int flags) {
    if (cmd->getkeys_proc) {
        return cmd->getkeys_proc(cmd,argv,argc,numkeys,flags);
    } else {
        return getKeysUsingCommandTable(cmd,argv,argc,numkeys);
    }
}
