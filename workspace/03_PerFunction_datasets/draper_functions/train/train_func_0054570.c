ompi_osc_base_find_available(bool enable_progress_threads,
                            bool enable_mpi_threads)
{
    mca_base_component_list_item_t *cli, *next;

    OPAL_LIST_FOREACH_SAFE(cli, next, &ompi_osc_base_framework.framework_components, mca_base_component_list_item_t) {
        int ret;
        ompi_osc_base_component_t *component = (ompi_osc_base_component_t*) cli->cli_component;


        ret = component->osc_init(enable_progress_threads, enable_mpi_threads);
        if (OMPI_SUCCESS != ret) {

            opal_list_remove_item(&ompi_osc_base_framework.framework_components, &cli->super);
            mca_base_component_close((mca_base_component_t *)component,
                                     ompi_osc_base_framework.framework_output);
            OBJ_RELEASE(cli);
        }
    }
    return OMPI_SUCCESS;
}
