task_backup_thread(void *arg)
{
    Slapi_PBlock *pb = (Slapi_PBlock *)arg;
    Slapi_Task *task = pb->pb_task;
    int rv;

    g_incr_active_threadcnt();
    slapi_task_begin(task, 1);

    slapi_task_log_notice(task, "Beginning backup of '%s'",
                          pb->pb_plugin->plg_name);
    LDAPDebug(LDAP_DEBUG_ANY, "Beginning backup of '%s'\n",
              pb->pb_plugin->plg_name, 0, 0);

    rv = (*pb->pb_plugin->plg_db2archive)(pb);
    if (rv != 0) {
        slapi_task_log_notice(task, "Backup failed (error %d)", rv);
        slapi_task_log_status(task, "Backup failed (error %d)", rv);
        LDAPDebug(LDAP_DEBUG_ANY, "Backup failed (error %d)\n", rv, 0, 0);
    } else {
        slapi_task_log_notice(task, "Backup finished.");
        slapi_task_log_status(task, "Backup finished.");
        LDAPDebug(LDAP_DEBUG_ANY, "Backup finished.\n", 0, 0, 0);
    }

    slapi_task_finish(task, rv);
    slapi_ch_free((void **)&pb->pb_seq_val);
    slapi_pblock_destroy(pb);
    g_decr_active_threadcnt();
}
