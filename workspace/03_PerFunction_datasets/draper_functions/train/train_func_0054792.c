orte_dt_std_print(char **output, char *prefix, void *src, opal_data_type_t type)
{

    *output = NULL;

    switch(type) {
        case ORTE_STD_CNTR:
            orte_dt_quick_print(output, "ORTE_STD_CNTR", prefix, src, ORTE_STD_CNTR_T);
            break;

        case ORTE_VPID:
            orte_dt_quick_print(output, "ORTE_VPID", prefix, src, ORTE_VPID_T);
            break;

        case ORTE_JOBID:
            asprintf(output, "%sData Type: ORTE_JOBID\tData size: %lu\tValue: %s",
                     (NULL == prefix) ? "" : prefix, (unsigned long)sizeof(orte_jobid_t),
                     ORTE_JOBID_PRINT(*(orte_jobid_t*)src));
            break;

        case ORTE_PROC_STATE:
            orte_dt_quick_print(output, "ORTE_PROC_STATE", prefix, src, ORTE_PROC_STATE_T);
            break;

        case ORTE_JOB_STATE:
            orte_dt_quick_print(output, "ORTE_JOB_STATE", prefix, src, ORTE_JOB_STATE_T);
            break;

        case ORTE_NODE_STATE:
            orte_dt_quick_print(output, "ORTE_NODE_STATE", prefix, src, ORTE_NODE_STATE_T);
            break;

        case ORTE_EXIT_CODE:
            orte_dt_quick_print(output, "ORTE_EXIT_CODE", prefix, src, ORTE_EXIT_CODE_T);
            break;

        case ORTE_RML_TAG:
            orte_dt_quick_print(output, "ORTE_RML_TAG", prefix, src, ORTE_RML_TAG_T);
            break;

        case ORTE_DAEMON_CMD:
            orte_dt_quick_print(output, "ORTE_DAEMON_CMD", prefix, src, ORTE_DAEMON_CMD_T);
            break;

        case ORTE_IOF_TAG:
            orte_dt_quick_print(output, "ORTE_IOF_TAG", prefix, src, ORTE_IOF_TAG_T);
            break;

        default:
            ORTE_ERROR_LOG(ORTE_ERR_UNKNOWN_DATA_TYPE);
            return ORTE_ERR_UNKNOWN_DATA_TYPE;
    }

    return ORTE_SUCCESS;
}
