globus_callback_get_timeout_threads(
    globus_reltime_t *                  time_left)
{
    globus_l_callback_restart_info_t *  restart_info;
    globus_l_callback_space_t *         i_space;
    globus_l_callback_info_t *          peek;
    globus_bool_t                       timedout;

    restart_info = (globus_l_callback_restart_info_t *)
        globus_thread_getspecific(globus_l_callback_restart_info_key);

    if(!restart_info || restart_info->own_thread)
    {
        GlobusTimeReltimeCopy(*time_left, globus_i_reltime_infinity);

        return GLOBUS_FALSE;
    }

    timedout = GLOBUS_FALSE;
    i_space = restart_info->callback_info->my_space;

    globus_mutex_lock(&i_space->lock);

    GlobusICallbackReadyPeak(&i_space->ready_queue, peek);

    if(peek)
    {
        GlobusTimeReltimeCopy(*time_left, globus_i_reltime_zero);

        timedout = GLOBUS_TRUE;
    }
    else
    {
        globus_abstime_t                time_now;
        const globus_abstime_t *        earlier_time;

        earlier_time = (globus_abstime_t *)
            globus_priority_q_first_priority(&i_space->timed_queue);

        if(!earlier_time ||
            globus_abstime_cmp(earlier_time, restart_info->time_stop) > 0)
        {
            earlier_time = restart_info->time_stop;
        }

        GlobusTimeAbstimeGetCurrent(time_now);
        if(globus_abstime_cmp(&time_now, earlier_time) >= 0)
        {
            GlobusTimeReltimeCopy(*time_left, globus_i_reltime_zero);

            timedout = GLOBUS_TRUE;
        }
        else if(globus_time_abstime_is_infinity(earlier_time))
        {
            GlobusTimeReltimeCopy(*time_left, globus_i_reltime_infinity);
        }
        else
        {
            GlobusTimeAbstimeDiff(*time_left, time_now, *earlier_time);
        }
    }

    globus_mutex_unlock(&i_space->lock);

    return timedout;
}
