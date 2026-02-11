orte_build_job_session_dir(char *top_dir,
                                        orte_process_name_t *proc,
                                        orte_jobid_t jobid)
{
    char *jobfam = NULL;
    char *job_session_dir;

    if (0 > asprintf(&jobfam, "%d", ORTE_JOB_FAMILY(proc->jobid))) {
        ORTE_ERROR_LOG(ORTE_ERR_OUT_OF_RESOURCE);
        return NULL;
    }

    if (ORTE_JOBID_WILDCARD != jobid) {
        char *job = NULL;

        if (0 > asprintf(&job, "%d", ORTE_LOCAL_JOBID(jobid))) {
            ORTE_ERROR_LOG(ORTE_ERR_OUT_OF_RESOURCE);
            job_session_dir = NULL;
            goto out;
        }
        job_session_dir = opal_os_path(false, top_dir, jobfam, job, NULL);
        free(job);
        if (NULL == job_session_dir) {
            ORTE_ERROR_LOG(ORTE_ERR_OUT_OF_RESOURCE);
        }
    } else {
        job_session_dir = opal_os_path(false, top_dir, jobfam, NULL);
        if( NULL == job_session_dir) {
            ORTE_ERROR_LOG(ORTE_ERR_OUT_OF_RESOURCE);
        }
    }

out:
    free(jobfam);
    return job_session_dir;
}
