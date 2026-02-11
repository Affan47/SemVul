globus_l_gass_copy_ftp_client_op_done_callback(
    void *                             user_arg,
    globus_ftp_client_handle_t *       handle,
    globus_object_t *                  err)
{
    globus_l_gass_copy_glob_info_t * info;

    info = (globus_l_gass_copy_glob_info_t *) user_arg;

    globus_mutex_lock(&info->mutex);
    if (err && !info->err)
    {
        info->err = globus_object_copy(err);
    }
    info->callbacks_left--;
    globus_cond_signal(&info->cond);
    globus_mutex_unlock(&info->mutex);

    return;
}
