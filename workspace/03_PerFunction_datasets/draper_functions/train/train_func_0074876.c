destruct_lmngr(mca_coll_ml_lmngr_t *lmngr)
{
    int max_nc = lmngr->n_resources;
    int rc, i;
    bcol_base_network_context_t *nc;
    opal_list_item_t *item;

    ML_VERBOSE(6, ("Destructing list manager %p", (void *)lmngr));

    while(!opal_list_is_empty(&lmngr->blocks_list)) {
        item = opal_list_remove_first(&lmngr->blocks_list);
        OBJ_DESTRUCT(item);
    }

    OBJ_DESTRUCT(&lmngr->blocks_list);

    if (NULL != lmngr->base_addr) {
        for( i = 0; i < max_nc; i++ ) {
            nc = lmngr->net_context[i];
            rc = nc->deregister_memory_fn(nc->context_data,
                    lmngr->reg_desc[nc->context_id]);
            if(rc != OMPI_SUCCESS) {
                ML_ERROR(("Failed to unregister , lmngr %p", (void *)lmngr));
            }
        }

        ML_VERBOSE(10, ("Release base addr %p", lmngr->base_addr));

        free(lmngr->base_addr);
        lmngr->base_addr = NULL;
    }

    lmngr->list_block_size = 0;
    lmngr->list_alignment = 0;
    lmngr->list_size = 0;

    OBJ_DESTRUCT(&lmngr->mem_lock);
}
