smsc2_stop_smsc(Octstr *id)
{
    SMSCConn *conn;
    long i = -1;
    int success = 0;

    if (!smsc_running)
        return -1;

    gw_rwlock_rdlock(&smsc_list_lock);

    while((i = smsc2_find(id, ++i)) != -1) {
        conn = gwlist_get(smsc_list, i);
        if (conn != NULL && smscconn_status(conn) == SMSCCONN_DEAD) {
            info(0, "HTTP: Could not shutdown already dead smsc-id `%s'",
                octstr_get_cstr(id));
        } else {
            info(0,"HTTP: Shutting down smsc-id `%s'", octstr_get_cstr(id));
            smscconn_shutdown(conn, 1);
            success = 1;
        }
    }
    gw_rwlock_unlock(&smsc_list_lock);
    if (success == 0) {
        error(0, "SMSC %s not found", octstr_get_cstr(id));
        return -1;
    }
    return 0;
}
