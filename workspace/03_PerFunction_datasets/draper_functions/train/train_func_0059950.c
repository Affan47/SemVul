mca_atomic_base_find_available(bool enable_progress_threads,
                                   bool enable_threads)
{
    mca_base_component_list_item_t *cli, *next;
    const mca_base_component_t *component;

    OPAL_LIST_FOREACH_SAFE(cli, next, &oshmem_atomic_base_framework.framework_components, mca_base_component_list_item_t) {
        component = cli->cli_component;


        if (OSHMEM_SUCCESS != init_query(component, enable_progress_threads,
                                       enable_threads)) {


            opal_list_remove_item(&oshmem_atomic_base_framework.framework_components, &cli->super);
            mca_base_component_close(component, oshmem_atomic_base_framework.framework_output);
            OBJ_RELEASE(cli);
        }
    }


    if (opal_list_get_size(&oshmem_atomic_base_framework.framework_components) == 0) {
        ATOMIC_VERBOSE(10,
                      "atomic:find_available: no components available!");
        return OSHMEM_ERROR;
    }


    return mca_atomic_base_select();
}
