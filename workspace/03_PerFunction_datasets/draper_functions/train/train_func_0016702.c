globus_options_init(
    globus_options_handle_t *           out_handle,
    globus_options_unknown_callback_t   unknown_func,
    void *                              unknown_arg)
{
    globus_l_options_handle_t *         handle;

    handle = (globus_l_options_handle_t *)
        globus_calloc(1, sizeof(globus_l_options_handle_t));
    if(handle == NULL)
    {
    }
    handle->unknown_func = unknown_func;
    handle->unknown_arg = unknown_arg;
    handle->table_list = NULL;

    *out_handle = handle;

    return GLOBUS_SUCCESS;
}
