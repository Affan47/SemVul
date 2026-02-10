cancelReplicationHandshake(void) {
    if (server.repl_state == REDIS_REPL_TRANSFER) {
        replicationAbortSyncTransfer();
    } else if (server.repl_state == REDIS_REPL_CONNECTING ||
               slaveIsInHandshakeState())
    {
        undoConnectWithMaster();
    } else {
        return 0;
    }
    return 1;
}
