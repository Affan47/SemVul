timer_cb(int fd, short event, void *cbdata)
{
    orte_job_t *jdata = (orte_job_t*)cbdata;


    ORTE_ACTIVATE_JOB_STATE(jdata, ORTE_JOB_STATE_FAILED_TO_START);


    OBJ_RELEASE(jdata->failure_timer);
}
