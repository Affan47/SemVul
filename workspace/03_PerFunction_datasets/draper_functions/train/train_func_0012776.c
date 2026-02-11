mca_topo_base_find_available(bool enable_progress_threads,
                                 bool enable_mpi_threads)
{
    opal_list_item_t *item, *next;
    mca_base_component_list_item_t *cli;


    item = opal_list_get_first(&ompi_topo_base_framework.framework_components);
    while (item != opal_list_get_end(&ompi_topo_base_framework.framework_components)) {
        next = opal_list_get_next(item);
         cli = (mca_base_component_list_item_t*)item;


         if (OMPI_SUCCESS != init_query(cli->cli_component, cli,
                                        enable_progress_threads,
                                        enable_mpi_threads)) {


             mca_base_component_repository_release(cli->cli_component);
             opal_list_remove_item(&ompi_topo_base_framework.framework_components, item);
             OBJ_RELEASE(item);
         }
         item = next;
     }


    if (0 == opal_list_get_size(&ompi_topo_base_framework.framework_components)) {
         opal_output_verbose (10, ompi_topo_base_framework.framework_output,
                              "topo:find_available: no topo components available!");
         return OMPI_ERROR;
     }


    return OMPI_SUCCESS;
}
