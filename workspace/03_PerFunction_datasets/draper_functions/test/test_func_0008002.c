mca_bcol_base_init(bool enable_progress_threads, bool enable_mpi_threads)
{
    mca_bcol_base_component_t *bcol_component;
    mca_base_component_list_item_t *cli;
    int ret;

    OPAL_LIST_FOREACH(cli, &mca_bcol_base_components_in_use, mca_base_component_list_item_t) {
        bcol_component = (mca_bcol_base_component_t *) cli->cli_component;

        if (false == bcol_component->init_done) {
            ret = bcol_component->collm_init_query(true, true);
            if (OMPI_SUCCESS != ret) {
                return ret;
            }

            bcol_component->init_done = true;
        }
    }

    return OMPI_SUCCESS;
}
