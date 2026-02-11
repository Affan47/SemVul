globus_l_gfs_reject_write_cb(
    globus_xio_handle_t                 handle,
    globus_result_t                     result,
    globus_byte_t *                     buffer,
    globus_size_t                       len,
    globus_size_t                       nbytes,
    globus_xio_data_descriptor_t        data_desc,
    void *                              user_arg)
{
    globus_mutex_lock(&globus_l_gfs_mutex);
    {
        if(user_arg)
        {
            globus_free(user_arg);
        }

        result = globus_xio_register_close(
            handle,
            NULL,
            globus_l_gfs_reject_close_cb,
            NULL);
        if(result != GLOBUS_SUCCESS)
        {
            if(globus_i_gfs_config_bool("inetd"))
            {
                globus_i_gfs_connection_closed();
            }
            else
            {
                globus_l_gfs_outstanding--;
            }
        }
    }
    globus_mutex_unlock(&globus_l_gfs_mutex);
}
