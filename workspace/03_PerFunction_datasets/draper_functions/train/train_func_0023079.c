mrhnp_complete(const orte_job_t *jdata)
{
    orte_job_t *jptr;
    orte_job_map_t *map;
    orte_proc_t *daemon;
    orte_iof_proc_t *proct;
    unsigned char data[1];
    opal_list_item_t *item;
    int i;
    orte_node_t *node;

    if (ORTE_JOBID_INVALID == jdata->stdout_target) {

        return;
    }


    jptr = orte_get_job_data_object(jdata->stdout_target);
    map = jptr->map;


    for (i=0; i < map->nodes->size; i++) {
        if (NULL == (node = (orte_node_t*)opal_pointer_array_get_item(map->nodes, i))) {
            continue;
        }
        daemon = node->daemon;
        if (daemon->name.vpid == ORTE_PROC_MY_NAME->vpid) {
            for (item = opal_list_get_first(&mca_iof_mr_hnp_component.procs);
                 item != opal_list_get_end(&mca_iof_mr_hnp_component.procs);
                 item = opal_list_get_next(item)) {
                proct = (orte_iof_proc_t*)item;
                if (proct->name.jobid == jptr->jobid) {
                    if (NULL != proct->sink) {

                        orte_iof_base_write_output(&proct->name, ORTE_IOF_STDIN, data, 0, proct->sink->wev);
                        proct->sink = NULL;
                    }
                }
            }
        } else {
            OPAL_OUTPUT_VERBOSE((1, orte_iof_base_framework.framework_output,
                                 "%s sending close stdin to daemon %s",
                                 ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                 ORTE_NAME_PRINT(&daemon->name)));


            send_data(&daemon->name, ORTE_IOF_STDIN, jptr->jobid, data, 0);
        }
    }
}
