ompi_osc_rdma_wait(ompi_win_t *win)
{
    ompi_osc_rdma_module_t *module = GET_MODULE(win);
    ompi_group_t *group;

    OPAL_OUTPUT_VERBOSE((25, ompi_osc_base_framework.framework_output,
                         "ompi_osc_rdma_wait entering..."));

    if (NULL == module->pw_group) {
        return OMPI_ERR_RMA_SYNC;
    }

    OPAL_THREAD_LOCK(&module->lock);
    while (0 != module->num_complete_msgs ||
             module->active_incoming_frag_count < module->active_incoming_frag_signal_count) {
        opal_condition_wait(&module->cond, &module->lock);
    }

    group = module->pw_group;
    module->pw_group = NULL;
    OPAL_THREAD_UNLOCK(&module->lock);

    ompi_group_decrement_proc_count(group);
    OBJ_RELEASE(group);

    OPAL_OUTPUT_VERBOSE((25, ompi_osc_base_framework.framework_output,
                         "ompi_osc_rdma_wait complete"));

    return OMPI_SUCCESS;
}
