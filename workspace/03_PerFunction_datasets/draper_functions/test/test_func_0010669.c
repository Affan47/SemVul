orte_routed_base_coll_peers(orte_grpcomm_collective_t *coll,
                                 opal_list_t *my_children)
{
    opal_list_item_t *item;
    orte_routed_tree_t *child;
    orte_namelist_t *nm;


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
