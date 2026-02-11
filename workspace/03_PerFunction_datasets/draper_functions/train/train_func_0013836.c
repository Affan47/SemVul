grdma_init(struct mca_mpool_base_resources_t *resources)
{
    mca_mpool_grdma_module_t* mpool_module;
    mca_mpool_grdma_pool_t *pool = NULL;
    opal_list_item_t *item;


    mca_mpool_grdma_component.leave_pinned = (int)
        (1 == ompi_mpi_leave_pinned || ompi_mpi_leave_pinned_pipeline);


    for (item = opal_list_get_first (&mca_mpool_grdma_component.pools) ;
         item != opal_list_get_end (&mca_mpool_grdma_component.pools) ;
         item = opal_list_get_next (item)) {
        pool = (mca_mpool_grdma_pool_t *) item;

        if (0 == strcmp (pool->pool_name, resources->pool_name)) {
            break;
        }

        pool = NULL;
    }

    if (NULL == pool) {

        pool = OBJ_NEW(mca_mpool_grdma_pool_t);
        if (NULL == pool) {
            return NULL;
        }

        pool->pool_name = strdup (resources->pool_name);

        opal_list_append (&mca_mpool_grdma_component.pools, &pool->super);
    }

    mpool_module =
        (mca_mpool_grdma_module_t *) malloc (sizeof (mca_mpool_grdma_module_t));

    mpool_module->resources = *resources;

    mca_mpool_grdma_module_init(mpool_module, pool);

    return &mpool_module->super;
}
