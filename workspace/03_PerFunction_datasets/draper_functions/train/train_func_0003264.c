snmp_read2(netsnmp_large_fd_set * fdset)
{
    struct session_list *slp;
    snmp_res_lock(MT_LIBRARY_ID, MT_LIB_SESSION);
    for (slp = Sessions; slp; slp = slp->next) {
        snmp_sess_read2((void *) slp, fdset);
    }
    snmp_res_unlock(MT_LIBRARY_ID, MT_LIB_SESSION);
}
