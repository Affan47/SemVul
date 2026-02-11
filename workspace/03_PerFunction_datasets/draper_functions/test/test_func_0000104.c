rsh_component_query(mca_base_module_t **module, int *priority)
{
    char *tmp;


    if (!mca_plm_rsh_component.disable_qrsh &&
        NULL != getenv("SGE_ROOT") && NULL != getenv("ARC") &&
        NULL != getenv("PE_HOSTFILE") && NULL != getenv("JOB_ID")) {

        asprintf(&tmp, "%s/bin/%s", getenv("SGE_ROOT"), getenv("ARC"));

        if (ORTE_SUCCESS != rsh_launch_agent_lookup("qrsh", tmp)) {

             opal_output_verbose(1, orte_plm_base_framework.framework_output,
                                "%s plm:rsh: unable to be used: SGE indicated but cannot find path "
                                "or execution permissions not set for launching agent qrsh",
                                ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
             free(tmp);
             *module = NULL;
             return ORTE_ERROR;
        }
        free(tmp);
        mca_plm_rsh_component.using_qrsh = true;

        mca_plm_rsh_component.no_tree_spawn = true;
        goto success;
    } else if (!mca_plm_rsh_component.disable_llspawn &&
               NULL != getenv("LOADL_STEP_ID")) {


        if (ORTE_SUCCESS != rsh_launch_agent_lookup("llspawn", NULL)) {
             opal_output_verbose(1, orte_plm_base_framework.framework_output,
                                "%s plm:rsh: unable to be used: LoadLeveler "
                                "indicated but cannot find path or execution "
                                "permissions not set for launching agent llspawn",
                                ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
            *module = NULL;
            return ORTE_ERROR;
        }
        mca_plm_rsh_component.using_llspawn = true;
        goto success;
    }


    if (ORTE_SUCCESS != rsh_launch_agent_lookup(NULL, NULL)) {

        OPAL_OUTPUT_VERBOSE((1, orte_plm_base_framework.framework_output,
                             "%s plm:rsh: unable to be used: cannot find path "
                             "for launching agent \"%s\"\n",
                             ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                             mca_plm_rsh_component.agent));
        *module = NULL;
        return ORTE_ERROR;
    }
success:

    *priority = mca_plm_rsh_component.priority;
    *module = (mca_base_module_t *) &orte_plm_rsh_module;
    return ORTE_SUCCESS;
}
