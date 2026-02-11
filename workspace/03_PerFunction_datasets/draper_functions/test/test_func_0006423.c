globus_l_gfs_data_get_nl_msg(
    globus_l_gfs_data_operation_t *     op)
{
    globus_xio_driver_list_ent_t *      ent;
    globus_result_t                     result;
    char *                              tmp_ptr;
    char *                              uuid;
    char *                              msg_out;
    globus_xio_attr_t                   xio_attr;


    if(op->session_handle->net_stack_list == NULL)
    {
        return NULL;
    }

    ent = globus_xio_driver_list_find_driver(
        op->session_handle->disk_stack_list,
        "netlogger");
    if(ent == NULL || ent->opts == NULL)
    {
        return NULL;
    }

    tmp_ptr = strstr(ent->opts, "uuid=");
    if(tmp_ptr == NULL)
    {
        return NULL;
    }

    uuid = strdup(tmp_ptr);
    tmp_ptr = strchr(uuid, ';');
    if(tmp_ptr != NULL)
    {
        *tmp_ptr = '\0';
    }


    globus_xio_attr_init(&xio_attr);
    result = globus_xio_attr_cntl(
        xio_attr,
        ent->driver,
        1024,
        uuid,
        &msg_out);
    globus_xio_attr_destroy(xio_attr);
    globus_free(uuid);
    if(result != GLOBUS_SUCCESS)
    {
        return NULL;
    }

    return msg_out;
}
