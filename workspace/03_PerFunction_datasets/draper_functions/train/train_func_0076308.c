mca_mpool_base_module_destroy(mca_mpool_base_module_t *module)
{
    mca_mpool_base_selected_module_t *sm, *next;

    OPAL_LIST_FOREACH_SAFE(sm, next, &mca_mpool_base_modules, mca_mpool_base_selected_module_t) {
        if (module == sm->mpool_module) {
            opal_list_remove_item(&mca_mpool_base_modules, (opal_list_item_t*)sm);
            if (NULL != sm->mpool_module->mpool_finalize) {
                sm->mpool_module->mpool_finalize(sm->mpool_module);
            }
            OBJ_RELEASE(sm);
            return OMPI_SUCCESS;
        }
    }

    return OMPI_ERR_NOT_FOUND;
}
