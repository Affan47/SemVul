BSDP_destroy(BSDP *bsdp){
    register gint i;
    if(bsdp->node_list)
        for(i = 0; i < bsdp->node_list->len; i++)
            BSDP_Node_destroy(bsdp, bsdp->node_list->pdata[i]);
    if(bsdp->node_list)
        g_ptr_array_free(bsdp->node_list, TRUE);
    RecycleBin_destroy(bsdp->edge_recycle);

    PQueueSet_destroy(bsdp->pqueue_set);
    if(bsdp->edge_filter)
        g_free(bsdp->edge_filter);
    if(bsdp->potential_recycle)
        RecycleBin_destroy(bsdp->potential_recycle);
    g_free(bsdp);
    return;
    }
