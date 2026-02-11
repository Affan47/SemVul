orte_grpcomm_base_pack_xcast(orte_jobid_t job,
                                 opal_buffer_t *buffer,
                                 opal_buffer_t *message,
                                 orte_rml_tag_t tag)
{
    orte_daemon_cmd_flag_t command;
    int rc;


    if (ORTE_RML_TAG_DAEMON != tag) {
        command = ORTE_DAEMON_MESSAGE_LOCAL_PROCS;
        if (ORTE_SUCCESS != (rc = opal_dss.pack(buffer, &command, 1, ORTE_DAEMON_CMD))) {
            ORTE_ERROR_LOG(rc);
            goto CLEANUP;
        }
        if (ORTE_SUCCESS != (rc = opal_dss.pack(buffer, &job, 1, ORTE_JOBID))) {
            ORTE_ERROR_LOG(rc);
            goto CLEANUP;
        }
        if (ORTE_SUCCESS != (rc = opal_dss.pack(buffer, &tag, 1, ORTE_RML_TAG))) {
            ORTE_ERROR_LOG(rc);
            goto CLEANUP;
        }
    }


    if (ORTE_SUCCESS != (rc = opal_dss.copy_payload(buffer, message))) {
        ORTE_ERROR_LOG(rc);
        goto CLEANUP;
    }

CLEANUP:
    return ORTE_SUCCESS;
}
