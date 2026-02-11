xioperf_read_cb(
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
        info->bytes_recv += nbytes;

        if(info->fptr != NULL && nbytes > 0)
        {

            fwrite(buffer, 1, nbytes, info->fptr);
        }
        info->ref--;
        if(result != GLOBUS_SUCCESS)
        {
            info->err = globus_error_get(result);
            goto error;
        }
        if(info->read_done || info->die)
        {

            goto error;
        }


        if(info->bytes_to_transfer == 0 ||
            info->bytes_recv < info->bytes_to_transfer ||
            !info->writer)
        {
            result = globus_xio_register_read(
                info->xio_handle,
                buffer,
                info->block_size,
                1,
                NULL,
                xioperf_read_cb,
                info);
            if(result != GLOBUS_SUCCESS)
            {
                info->err = globus_error_get(result);
                goto error;
            }
            info->ref++;
        }
        else
        {
            info->read_done = GLOBUS_TRUE;
            globus_cond_signal(&info->cond);
        }
    }
    globus_mutex_unlock(&info->mutex);

    return;
error:
    globus_free(buffer);
    info->read_done = GLOBUS_TRUE;
    globus_cond_signal(&info->cond);
    globus_mutex_unlock(&info->mutex);
}
