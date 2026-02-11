smsc2_resume(void)
{
    SMSCConn *conn;
    long i;

    if (!smsc_running)
        return;

    gw_rwlock_rdlock(&smsc_list_lock);
    for (i = 0; i < gwlist_len(smsc_list); i++) {
        conn = gwlist_get(smsc_list, i);
        smscconn_start(conn);
    }
    gw_rwlock_unlock(&smsc_list_lock);

    if (router_thread >= 0)
        gwthread_wakeup(router_thread);
}
