globus_callback_space_init_nothreads(
    globus_callback_space_t *           space,
    globus_callback_space_attr_t        attr)
{
    globus_l_callback_space_t *         i_space;

    if(!space)
    {
        return GLOBUS_L_CALLBACK_CONSTRUCT_INVALID_ARGUMENT(
            "globus_callback_space_init", "space");
    }

    i_space = (globus_l_callback_space_t *)
        globus_memory_pop_node(&globus_l_callback_space_memory);
    if(!i_space)
    {
        return GLOBUS_L_CALLBACK_CONSTRUCT_MEMORY_ALLOC(
            "globus_callback_space_init", "i_space");
    }

    GlobusICallbackReadyInit(&i_space->ready_queue);
    globus_priority_q_init(
        &i_space->timed_queue,
        (globus_priority_q_cmp_func_t) globus_abstime_cmp);

    i_space->handle =
        globus_handle_table_insert(
            &globus_l_callback_space_table, i_space, 1);
    i_space->depth = 0;

    *space = i_space->handle;

    return GLOBUS_SUCCESS;
}
