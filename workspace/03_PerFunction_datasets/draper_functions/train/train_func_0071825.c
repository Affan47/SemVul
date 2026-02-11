get_orted_comm_cmd_str(int command)
{
    switch(command) {
    case ORTE_DAEMON_NULL_CMD:
        return strdup("NULL");
    case ORTE_DAEMON_KILL_LOCAL_PROCS:
        return strdup("ORTE_DAEMON_KILL_LOCAL_PROCS");
    case ORTE_DAEMON_SIGNAL_LOCAL_PROCS:
        return strdup("ORTE_DAEMON_SIGNAL_LOCAL_PROCS");
    case ORTE_DAEMON_ADD_LOCAL_PROCS:
        return strdup("ORTE_DAEMON_ADD_LOCAL_PROCS");
    case ORTE_DAEMON_TREE_SPAWN:
        return strdup("ORTE_DAEMON_TREE_SPAWN");
    case ORTE_DAEMON_MESSAGE_LOCAL_PROCS:
        return strdup("ORTE_DAEMON_MESSAGE_LOCAL_PROCS");
     case ORTE_DAEMON_EXIT_CMD:
        return strdup("ORTE_DAEMON_EXIT_CMD");
    case ORTE_DAEMON_SPAWN_JOB_CMD:
        return strdup("ORTE_DAEMON_SPAWN_JOB_CMD");
    case ORTE_DAEMON_CONTACT_QUERY_CMD:
        return strdup("ORTE_DAEMON_CONTACT_QUERY_CMD");
    case ORTE_DAEMON_REPORT_JOB_INFO_CMD:
        return strdup("ORTE_DAEMON_REPORT_JOB_INFO_CMD");
    case ORTE_DAEMON_REPORT_NODE_INFO_CMD:
        return strdup("ORTE_DAEMON_REPORT_NODE_INFO_CMD");
    case ORTE_DAEMON_REPORT_PROC_INFO_CMD:
        return strdup("ORTE_DAEMON_REPORT_PROC_INFO_CMD");
    case ORTE_DAEMON_HEARTBEAT_CMD:
        return strdup("ORTE_DAEMON_HEARTBEAT_CMD");
    case ORTE_DAEMON_SYNC_BY_PROC:
        return strdup("ORTE_DAEMON_SYNC_BY_PROC");
    case ORTE_DAEMON_SYNC_WANT_NIDMAP:
        return strdup("ORTE_DAEMON_SYNC_WANT_NIDMAP");
    case ORTE_DAEMON_TOP_CMD:
        return strdup("ORTE_DAEMON_TOP_CMD");
    case ORTE_DAEMON_ABORT_CALLED:
        return strdup("ORTE_DAEMON_ABORT_CALLED");
    case ORTE_DAEMON_ABORT_PROCS_CALLED:
        return strdup("ORTE_DAEMON_ABORT_PROCS_CALLED");
    default:
        return strdup("Unknown Command!");
    }
}
