orte_iof_mrhnp_recv(int status, orte_process_name_t* sender,
                       opal_buffer_t* buffer, orte_rml_tag_t tag,
                       void* cbdata)
{
    orte_process_name_t origin;
    unsigned char data[ORTE_IOF_BASE_MSG_MAX];
    orte_iof_tag_t stream;
    int32_t count, numbytes;
    int rc;


    count = 1;
    if (ORTE_SUCCESS != (rc = opal_dss.unpack(buffer, &stream, &count, ORTE_IOF_TAG))) {
        ORTE_ERROR_LOG(rc);
        goto CLEAN_RETURN;
    }

    if (ORTE_IOF_XON & stream) {

        if (NULL != mca_iof_mr_hnp_component.stdinev &&
            !orte_job_term_ordered &&
            !mca_iof_mr_hnp_component.stdinev->active) {
            mca_iof_mr_hnp_component.stdinev->active = true;
            opal_event_add(mca_iof_mr_hnp_component.stdinev->ev, 0);
        }
        goto CLEAN_RETURN;
    } else if (ORTE_IOF_XOFF & stream) {

        if (NULL != mca_iof_mr_hnp_component.stdinev &&
            !mca_iof_mr_hnp_component.stdinev->active) {
            opal_event_del(mca_iof_mr_hnp_component.stdinev->ev);
            mca_iof_mr_hnp_component.stdinev->active = false;
        }
        goto CLEAN_RETURN;
    }


    count = 1;
    if (ORTE_SUCCESS != (rc = opal_dss.unpack(buffer, &origin, &count, ORTE_NAME))) {
        ORTE_ERROR_LOG(rc);
        goto CLEAN_RETURN;
    }


    numbytes=ORTE_IOF_BASE_MSG_MAX;
    if (ORTE_SUCCESS != (rc = opal_dss.unpack(buffer, data, &numbytes, OPAL_BYTE))) {
        ORTE_ERROR_LOG(rc);
        goto CLEAN_RETURN;
    }


    OPAL_OUTPUT_VERBOSE((1, orte_iof_base_framework.framework_output,
                         "%s unpacked %d bytes from remote proc %s",
                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), numbytes,
                         ORTE_NAME_PRINT(&origin)));


    if (ORTE_IOF_STDOUT & stream || orte_xml_output) {
        orte_iof_base_write_output(&origin, stream, data, numbytes, orte_iof_base.iof_write_stdout->wev);
    } else {
        orte_iof_base_write_output(&origin, stream, data, numbytes, orte_iof_base.iof_write_stderr->wev);
    }

CLEAN_RETURN:
    return;
}
