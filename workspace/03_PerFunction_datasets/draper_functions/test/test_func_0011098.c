update_routing_plan(void)
{
    orte_routed_tree_t *child;
    opal_list_item_t *item;
    int my_vpid = ORTE_PROC_MY_NAME->vpid;
    int i;


    if (!ORTE_PROC_IS_DAEMON && !ORTE_PROC_IS_HNP) {
        return;
    }


    while (NULL != (item = opal_list_remove_first(&my_children))) {
        OBJ_RELEASE(item);
    }

    log_nranks = (int) ilog2 ((unsigned int)orte_process_info.num_procs) ;
    assert(log_nranks < 31);

    if (log_nranks < 3) {
      log_npeers = 1;
    } else if (log_nranks < 7) {
      log_npeers = 2;
    } else {
      log_npeers = 4;
    }


    log_nranks = ((log_nranks + log_npeers) & ~(log_npeers - 1)) - 1;

    rank_mask = (1 << (log_nranks + 1)) - 1;


    ORTE_PROC_MY_PARENT->vpid = my_vpid ? my_vpid >> log_npeers : -1;


    if ((my_vpid >> (log_nranks + 1 - log_npeers)) == 0) {
        for (i = (1 << log_npeers) - 1 ; i >= 0 ; --i) {
            int next = ((my_vpid << log_npeers) | i) & rank_mask;


            if (next > my_vpid && next < (int)orte_process_info.num_procs) {
                child = OBJ_NEW(orte_routed_tree_t);
                child->vpid = next;
                opal_list_append (&my_children, &child->super);
            }
        }
    }
}
