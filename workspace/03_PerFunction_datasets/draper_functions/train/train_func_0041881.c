xioperf_write_cb(
    globus_xio_handle_t                 handle,
    globus_result_t                     result,
    globus_byte_t *                     buffer,
    globus_size_t                       len,
    globus_size_t                       nbytes,
    globus_xio_data_descriptor_t        data_desc,
    void *                              user_arg)
{
    globus_i_xioperf_info_t *           info;

    info = (globus_i_xioperf_info_t *) user_arg;

    globus_mutex_lock(&info->mutex);
    {
        globus_free(buffer);
        info->bytes_sent += nbytes;
        info->ref--;
        if(result != GLOBUS_SUCCESS)
        {
            goto error;
        }
        if(info->bytes_to_transfer > 0 &&
            info->bytes_sent >= info->bytes_to_transfer)
        {
            info->write_done = GLOBUS_TRUE;
        }
        if(!info->write_done)
        {
            result = xioperf_next_write(info);
            if(result != GLOBUS_SUCCESS)
            {
                goto error;
            }
        }
        globus_cond_signal(&info->cond);
    }
    globus_mutex_unlock(&info->mutex);

    return;
error:

    if(!globus_xio_error_is_canceled(result))
    {
        xioperf_l_log("write_cb error: ", result);
    }
    info->err = globus_error_get(result);
    info->write_done = GLOBUS_TRUE;
    globus_cond_signal(&info->cond);
    globus_mutex_unlock(&info->mutex);
}
