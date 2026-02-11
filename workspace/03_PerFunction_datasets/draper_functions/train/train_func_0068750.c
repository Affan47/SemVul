orte_ras_slurm_component_query(mca_base_module_t **module, int *priority)
{


    if (NULL == getenv("SLURM_JOBID") &&
        !mca_ras_slurm_component.dyn_alloc_enabled) {

        *priority = 0;
        *module = NULL;
        return ORTE_ERROR;
    }

    OPAL_OUTPUT_VERBOSE((2, orte_ras_base_framework.framework_output,
                         "%s ras:slurm: available for selection",
                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME)));


    *priority = 50;
    *module = (mca_base_module_t *) &orte_ras_slurm_module;
    return ORTE_SUCCESS;
}
