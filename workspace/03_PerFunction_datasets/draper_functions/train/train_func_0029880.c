orte_util_comm_halt_vm(const orte_process_name_t *hnp)
{
    opal_buffer_t *buf;
    orte_daemon_cmd_flag_t command;
    int rc;

    OPAL_OUTPUT_VERBOSE((5, orte_debug_output,
                         "%s util_comm_halt_vm: ordering HNP %s terminate",
                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                         ORTE_NAME_PRINT(hnp)));


    buf = OBJ_NEW(opal_buffer_t);


    command = ORTE_DAEMON_HALT_VM_CMD;
    if (ORTE_SUCCESS != (rc = opal_dss.pack(buf, &command, 1, ORTE_DAEMON_CMD))) {
        ORTE_ERROR_LOG(rc);
        OBJ_RELEASE(buf);
        goto CLEANUP;
    }


    if (0 > (rc = orte_rml.send_buffer_nb((orte_process_name_t*)hnp, buf,
                                          ORTE_RML_TAG_DAEMON,
                                          orte_rml_send_callback, NULL))) {
        ORTE_ERROR_LOG(rc);
        OBJ_RELEASE(buf);
        goto CLEANUP;
    }
    OBJ_RELEASE(buf);


CLEANUP:
    return rc;
}
