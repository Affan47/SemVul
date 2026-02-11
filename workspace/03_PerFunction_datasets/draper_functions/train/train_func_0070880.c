orte_state_base_activate_job_state(orte_job_t *jdata,
                                        orte_job_state_t state)
{
    opal_list_item_t *itm, *any=NULL, *error=NULL;
    orte_state_t *s;
    orte_state_caddy_t *caddy;

    for (itm = opal_list_get_first(&orte_job_states);
         itm != opal_list_get_end(&orte_job_states);
         itm = opal_list_get_next(itm)) {
        s = (orte_state_t*)itm;
        if (s->job_state == ORTE_JOB_STATE_ANY) {

            any = itm;
        }
        if (s->job_state == ORTE_JOB_STATE_ERROR) {
            error = itm;
        }
        if (s->job_state == state) {
            OPAL_OUTPUT_VERBOSE((1, orte_state_base_framework.framework_output,
                                 "%s ACTIVATING JOB %s STATE %s PRI %d",
                                 ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                 (NULL == jdata) ? "NULL" : ORTE_JOBID_PRINT(jdata->jobid),
                                 orte_job_state_to_str(state), s->priority));
            if (NULL == s->cbfunc) {
                OPAL_OUTPUT_VERBOSE((1, orte_state_base_framework.framework_output,
                                     "%s NULL CBFUNC FOR JOB %s STATE %s",
                                     ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                     (NULL == jdata) ? "ALL" : ORTE_JOBID_PRINT(jdata->jobid),
                                     orte_job_state_to_str(state)));
                return;
            }
            caddy = OBJ_NEW(orte_state_caddy_t);
            if (NULL != jdata) {
                caddy->jdata = jdata;
                caddy->job_state = state;
                OBJ_RETAIN(jdata);
            }
            opal_event_set(orte_event_base, &caddy->ev, -1, OPAL_EV_WRITE, s->cbfunc, caddy);
            opal_event_set_priority(&caddy->ev, s->priority);
            opal_event_active(&caddy->ev, OPAL_EV_WRITE, 1);
            return;
        }
    }


    if (ORTE_JOB_STATE_ERROR < state && NULL != error) {
        s = (orte_state_t*)error;
    } else if (NULL != any) {
        s = (orte_state_t*)any;
    } else {
        OPAL_OUTPUT_VERBOSE((1, orte_state_base_framework.framework_output,
                             "ACTIVATE: ANY STATE NOT FOUND"));
        return;
    }
    if (NULL == s->cbfunc) {
        OPAL_OUTPUT_VERBOSE((1, orte_state_base_framework.framework_output,
                             "ACTIVATE: ANY STATE HANDLER NOT DEFINED"));
        return;
    }
    caddy = OBJ_NEW(orte_state_caddy_t);
    if (NULL != jdata) {
        caddy->jdata = jdata;
        caddy->job_state = state;
        OBJ_RETAIN(jdata);
    }
            OPAL_OUTPUT_VERBOSE((1, orte_state_base_framework.framework_output,
                                 "%s ACTIVATING JOB %s STATE %s PRI %d",
                                 ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                 (NULL == jdata) ? "NULL" : ORTE_JOBID_PRINT(jdata->jobid),
                                 orte_job_state_to_str(state), s->priority));
    opal_event_set(orte_event_base, &caddy->ev, -1, OPAL_EV_WRITE, s->cbfunc, caddy);
    opal_event_set_priority(&caddy->ev, s->priority);
    opal_event_active(&caddy->ev, OPAL_EV_WRITE, 1);
}
