globus_l_gass_copy_glob_ftp_list(
    globus_l_gass_copy_glob_info_t *    info)
{
    static char *   myname = "globus_l_gass_copy_glob_ftp_list";

    globus_result_t                     result;
    globus_byte_t *                     read_buffer;

    read_buffer = (globus_byte_t *)
        globus_malloc(GLOBUS_GASS_COPY_FTP_LIST_BUFFER_SIZE *
            sizeof(globus_byte_t));

    if(read_buffer == GLOBUS_NULL)
    {
        result = globus_error_put(
            globus_error_construct_string(
            GLOBUS_GASS_COPY_MODULE,
            GLOBUS_NULL,
            "[%s]: Memory allocation error",
            myname));
        goto error_malloc;
    }


    info->callbacks_left = 2;
    if(info->list_op == GLOBUS_GASS_COPY_FTP_OP_MLSD)
    {
        result = globus_ftp_client_machine_list(
                     &info->handle->ftp_handle,
                     info->base_url,
                     info->attr->ftp_attr,
                     globus_l_gass_copy_ftp_client_op_done_callback,
                     info);
    }
    else
    {
        result = globus_ftp_client_list(
                     &info->handle->ftp_handle,
                     info->base_url,
                     info->attr->ftp_attr,
                     globus_l_gass_copy_ftp_client_op_done_callback,
                     info);
    }

    if(result != GLOBUS_SUCCESS)
    {
        goto error_list;
    }

    result = globus_ftp_client_register_read(
                 &info->handle->ftp_handle,
                 read_buffer,
                 GLOBUS_GASS_COPY_FTP_LIST_BUFFER_SIZE,
                 globus_l_gass_copy_ftp_client_list_read_callback,
                 info);

    if(result != GLOBUS_SUCCESS)
    {
        globus_ftp_client_abort(&info->handle->ftp_handle);

        globus_mutex_lock(&info->mutex);
        info->callbacks_left--;
        while(info->callbacks_left > 0)
        {
            globus_cond_wait(&info->cond, &info->mutex);
        }
        globus_mutex_unlock(&info->mutex);

        goto error_read;
    }

    globus_mutex_lock(&info->mutex);
    while(info->callbacks_left)
    {
        globus_cond_wait(&info->cond, &info->mutex);
    }
    globus_mutex_unlock(&info->mutex);

    if(info->err)
    {
        result = globus_error_put(info->err);
        info->err = GLOBUS_NULL;
    }

    if(result != GLOBUS_SUCCESS)
    {
        goto error_read;
    }

    if(read_buffer != (globus_byte_t *) info->list_buffer)
    {
        globus_free(read_buffer);
    }


    return GLOBUS_SUCCESS;


error_read:
error_list:

    if(read_buffer != GLOBUS_NULL)
    {
        globus_free(read_buffer);
    }
    if(info->err)
    {
        globus_object_free(info->err);
        info->err = GLOBUS_NULL;
    }

error_malloc:
    return result;
}
