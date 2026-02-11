ompi_op_base_find_available(bool enable_progress_threads,
                                bool enable_mpi_threads)
{
    mca_base_component_list_item_t *cli, *next;


    OPAL_LIST_FOREACH_SAFE(cli, next, &ompi_op_base_framework.framework_components, mca_base_component_list_item_t) {
        const mca_base_component_t *component = cli->cli_component;


        if (OMPI_SUCCESS != init_query(component,
                                       enable_progress_threads,
                                       enable_mpi_threads)) {


            opal_list_remove_item(&ompi_op_base_framework.framework_components, &cli->super);
            mca_base_component_close(component, ompi_op_base_framework.framework_output);
            OBJ_RELEASE(cli);
        }
    }


    return OMPI_SUCCESS;
}
