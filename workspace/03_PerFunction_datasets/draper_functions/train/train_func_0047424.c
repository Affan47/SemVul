orte_routed_base_xcast_routing(orte_grpcomm_collective_t *coll,
                                    opal_list_t *my_children)
{
    opal_list_item_t *item;
    orte_routed_tree_t *child;
    orte_namelist_t *nm;
    int i;
    orte_proc_t *proc;
    orte_job_t *daemons;


    if (ORTE_PROC_IS_HNP) {
        if (orte_abnormal_term_ordered) {
            daemons = orte_get_job_data_object(ORTE_PROC_MY_NAME->jobid);
            for (i=1; i < daemons->procs->size; i++) {
                if (NULL == (proc = (orte_proc_t*)opal_pointer_array_get_item(daemons->procs, i))) {
                    continue;
                }

                if (proc->alive) {
                    nm = OBJ_NEW(orte_namelist_t);
                    nm->name.jobid = ORTE_PROC_MY_NAME->jobid;
                    nm->name.vpid = proc->name.vpid;
                    opal_list_append(&coll->targets, &nm->super);
                }
            }
        } else {

            for (item = opal_list_get_first(my_children);
                 item != opal_list_get_end(my_children);
                 item = opal_list_get_next(item)) {
                child = (orte_routed_tree_t*)item;
                nm = OBJ_NEW(orte_namelist_t);
                nm->name.jobid = ORTE_PROC_MY_NAME->jobid;
                nm->name.vpid = child->vpid;
                opal_list_append(&coll->targets, &nm->super);
            }
        }
    } else {

        for (item = opal_list_get_first(my_children);
             item != opal_list_get_end(my_children);
             item = opal_list_get_next(item)) {
            child = (orte_routed_tree_t*)item;
            nm = OBJ_NEW(orte_namelist_t);
            nm->name.jobid = ORTE_PROC_MY_NAME->jobid;
            nm->name.vpid = child->vpid;
            opal_list_append(&coll->targets, &nm->super);
        }
    }
}
