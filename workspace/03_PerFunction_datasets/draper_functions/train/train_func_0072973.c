rte_init(void)
{
    int ret;
    char *error = NULL;
    char **hosts = NULL;


    if (ORTE_SUCCESS != (ret = orte_ess_base_std_prolog())) {
        error = "orte_ess_base_std_prolog";
        goto error;
    }


    env_set_name();


    if (ORTE_PROC_IS_DAEMON) {
        if (NULL != orte_node_regex) {

            if (ORTE_SUCCESS != (ret = orte_regex_extract_node_names(orte_node_regex, &hosts))) {
                error = "orte_regex_extract_node_names";
                goto error;
            }
        }
        if (ORTE_SUCCESS != (ret = orte_ess_base_orted_setup(hosts))) {
            ORTE_ERROR_LOG(ret);
            error = "orte_ess_base_orted_setup";
            goto error;
        }
        opal_argv_free(hosts);
        return ORTE_SUCCESS;
    }

    if (ORTE_PROC_IS_TOOL) {

        if (ORTE_SUCCESS != (ret = orte_ess_base_tool_setup())) {
            ORTE_ERROR_LOG(ret);
            error = "orte_ess_base_tool_setup";
            goto error;
        }

        return ORTE_SUCCESS;

    }


    putenv("OMPI_MCA_db=^pmi");


    if (ORTE_SUCCESS != (ret = orte_ess_base_app_setup())) {
        ORTE_ERROR_LOG(ret);
        error = "orte_ess_base_app_setup";
        goto error;
    }


    if (ORTE_SUCCESS != (ret = orte_util_nidmap_init(orte_process_info.sync_buf))) {
        ORTE_ERROR_LOG(ret);
        error = "orte_util_nidmap_init";
        goto error;
    }


    if (ORTE_SUCCESS != (ret = orte_ess_base_proc_binding())) {
        error = "proc_binding";
        goto error;
    }

    return ORTE_SUCCESS;

error:
    if (ORTE_ERR_SILENT != ret && !orte_report_silent_errors) {
        orte_show_help("help-orte-runtime.txt",
                       "orte_init:startup:internal-failure",
                       true, error, ORTE_ERROR_NAME(ret), ret);
    }

    return ret;
}
