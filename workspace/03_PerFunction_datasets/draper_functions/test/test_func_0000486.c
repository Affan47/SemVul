toggle_locked(item *op) {
    SockList sl;
    uint8 buf[MAX_BUF];

    if (op->env->tag == 0) {
        return;
    }

    snprintf((char*)buf, sizeof(buf), "lock %c %d", !op->locked, op->tag);
    script_monitor_str((char*)buf);
    SockList_Init(&sl, buf);
    SockList_AddString(&sl, "lock ");
    SockList_AddChar(&sl, !op->locked);
    SockList_AddInt(&sl, op->tag);
    SockList_Send(&sl, csocket.fd);
}
