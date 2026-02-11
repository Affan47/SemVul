gather_nodes(orte_ps_mpirun_info_t *hnpinfo) {
    int ret;

    if (ORTE_SUCCESS != (ret = orte_util_comm_query_node_info(&(hnpinfo->hnp->name), NULL,
                                                             &hnpinfo->num_nodes, &hnpinfo->nodes))) {
        ORTE_ERROR_LOG(ret);
    }

    return ret;
}
