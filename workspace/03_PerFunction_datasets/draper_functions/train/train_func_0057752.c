globus_l_callback_space_destructor(
    void *                              datum)
{
    globus_l_callback_space_t *         i_space;
    globus_bool_t                       clean_up;

    i_space = (globus_l_callback_space_t *) datum;

    clean_up = GLOBUS_TRUE;

    if(i_space->behavior == GLOBUS_CALLBACK_SPACE_BEHAVIOR_SERIALIZED)
    {
        globus_mutex_lock(&globus_l_callback_thread_lock);
        {
            if(!globus_l_callback_shutting_down)
            {
                globus_mutex_lock(&i_space->lock);
                {
                    i_space->shutdown = GLOBUS_TRUE;
                    globus_cond_broadcast(&i_space->cond);
                }
                globus_mutex_unlock(&i_space->lock);

                globus_list_remove(
                    &globus_l_callback_threaded_spaces,
                    globus_list_search(
                        globus_l_callback_threaded_spaces, i_space));


                clean_up = GLOBUS_FALSE;
            }
        }
        globus_mutex_unlock(&globus_l_callback_thread_lock);
    }

    if(clean_up)
    {
        globus_priority_q_destroy(&i_space->timed_queue);
        globus_mutex_destroy(&i_space->lock);
        globus_cond_destroy(&i_space->cond);

        globus_memory_push_node(
            &globus_l_callback_space_memory, i_space);
    }
}
