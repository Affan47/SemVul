globus_callback_unregister_threads(
    globus_callback_handle_t            callback_handle,
    globus_callback_func_t              unregister_callback,
    void *                              unreg_arg,
    globus_bool_t *                     active)
{
    globus_l_callback_info_t *          callback_info;

    globus_mutex_lock(&globus_l_callback_handle_lock);
    {
        callback_info = (globus_l_callback_info_t *)
            globus_handle_table_lookup(
                &globus_l_callback_handle_table, callback_handle);
    }
    globus_mutex_unlock(&globus_l_callback_handle_lock);

    if(!callback_info)
    {


        return GLOBUS_L_CALLBACK_CONSTRUCT_INVALID_CALLBACK_HANDLE(
            "globus_callback_unregister");
    }

    globus_mutex_lock(&callback_info->my_space->lock);


    if(callback_info->unregister_callback)
    {
        globus_mutex_unlock(&callback_info->my_space->lock);

        return GLOBUS_L_CALLBACK_CONSTRUCT_ALREADY_CANCELED(
            "globus_callback_unregister");
    }

    callback_info->unregister_callback = unregister_callback;
    callback_info->unreg_arg = unreg_arg;

    if(callback_info->running_count > 0)
    {
        if(callback_info->is_periodic)
        {

            if(callback_info->in_queue == GLOBUS_L_CALLBACK_QUEUE_TIMED)
            {
                globus_priority_q_remove(
                    &callback_info->my_space->timed_queue, callback_info);
            }
            else if(callback_info->in_queue == GLOBUS_L_CALLBACK_QUEUE_READY)
            {
                GlobusICallbackReadyRemove(
                    &callback_info->my_space->ready_queue, callback_info);
            }

            callback_info->in_queue = GLOBUS_L_CALLBACK_QUEUE_NONE;
            callback_info->is_periodic = GLOBUS_FALSE;
        }

        globus_mutex_unlock(&callback_info->my_space->lock);


        globus_l_callback_info_dec_ref(callback_handle);

        if(active)
        {
            *active = GLOBUS_TRUE;
        }

        return GLOBUS_SUCCESS;
    }
    else
    {


        if(callback_info->in_queue)
        {
            if(callback_info->in_queue == GLOBUS_L_CALLBACK_QUEUE_TIMED)
            {
                globus_priority_q_remove(
                    &callback_info->my_space->timed_queue, callback_info);
            }
            else if(callback_info->in_queue == GLOBUS_L_CALLBACK_QUEUE_READY)
            {
                GlobusICallbackReadyRemove(
                    &callback_info->my_space->ready_queue, callback_info);
            }

            callback_info->in_queue = GLOBUS_L_CALLBACK_QUEUE_NONE;


            globus_l_callback_info_dec_ref(callback_handle);
        }

        globus_mutex_unlock(&callback_info->my_space->lock);

        if(unregister_callback)
        {
            globus_callback_space_register_oneshot(
                GLOBUS_NULL,
                GLOBUS_NULL,
                globus_l_callback_cancel_kickout_cb,
                callback_info,
                callback_info->my_space->handle);
        }
        else
        {

            globus_l_callback_info_dec_ref(callback_handle);
        }

        if(active)
        {
            *active = GLOBUS_FALSE;
        }

        return GLOBUS_SUCCESS;
    }
}
