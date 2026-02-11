delete_route(orte_process_name_t *proc)
{
    int i;
    orte_routed_jobfam_t *jfam;
    uint16_t jfamily;

    if (proc->jobid == ORTE_JOBID_INVALID ||
        proc->vpid == ORTE_VPID_INVALID) {
        return ORTE_ERR_BAD_PARAM;
    }


    if (!ORTE_PROC_IS_HNP && !ORTE_PROC_IS_DAEMON &&
        !ORTE_PROC_IS_TOOL) {
        return ORTE_SUCCESS;
    }

    OPAL_OUTPUT_VERBOSE((1, orte_routed_base_framework.framework_output,
                         "%s routed_radix_delete_route for %s",
                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                         ORTE_NAME_PRINT(proc)));


    if (ORTE_JOB_FAMILY(proc->jobid) != ORTE_JOB_FAMILY(ORTE_PROC_MY_NAME->jobid)) {


        if (ORTE_PROC_IS_DAEMON) {
            return ORTE_SUCCESS;
        }


        jfamily = ORTE_JOB_FAMILY(proc->jobid);
        for (i=0; i < orte_routed_jobfams.size; i++) {
            if (NULL == (jfam = (orte_routed_jobfam_t*)opal_pointer_array_get_item(&orte_routed_jobfams, i))) {
                continue;
            }
            if (jfam->job_family == jfamily) {
                OPAL_OUTPUT_VERBOSE((2, orte_routed_base_framework.framework_output,
                                     "%s routed_binomial: deleting route to %s",
                                     ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                     ORTE_JOB_FAMILY_PRINT(proc->jobid)));
                opal_pointer_array_set_item(&orte_routed_jobfams, i, NULL);
                OBJ_RELEASE(jfam);
                return ORTE_SUCCESS;
            }
        }

        return ORTE_SUCCESS;
    }


    return ORTE_SUCCESS;
}
