orte_filem_base_recv(int status, orte_process_name_t* sender,
                        opal_buffer_t* buffer, orte_rml_tag_t tag,
                        void* cbdata)
{
    orte_filem_cmd_flag_t command;
    orte_std_cntr_t count;
    int rc;

    OPAL_OUTPUT_VERBOSE((5, orte_filem_base_framework.framework_output,
                         "%s filem:base: Receive a command message.",
                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME)));

    count = 1;
    if (ORTE_SUCCESS != (rc = opal_dss.unpack(buffer, &command, &count, ORTE_FILEM_CMD))) {
        ORTE_ERROR_LOG(rc);
        return;
    }

    switch (command) {
        case ORTE_FILEM_GET_PROC_NODE_NAME_CMD:
            OPAL_OUTPUT_VERBOSE((10, orte_filem_base_framework.framework_output,
                                 "%s filem:base: Command: Get Proc node name command",
                                 ORTE_NAME_PRINT(ORTE_PROC_MY_NAME)));

            filem_base_process_get_proc_node_name_cmd(sender, buffer);
            break;

        case ORTE_FILEM_GET_REMOTE_PATH_CMD:
            OPAL_OUTPUT_VERBOSE((10, orte_filem_base_framework.framework_output,
                                 "%s filem:base: Command: Get remote path command",
                                 ORTE_NAME_PRINT(ORTE_PROC_MY_NAME)));

            filem_base_process_get_remote_path_cmd(sender, buffer);
            break;

        default:
            ORTE_ERROR_LOG(ORTE_ERR_VALUE_OUT_OF_BOUNDS);
    }
}
