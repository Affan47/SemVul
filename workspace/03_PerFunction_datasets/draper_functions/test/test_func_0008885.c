globus_i_gram_usage_start_session_stats(
    globus_gram_job_manager_t *         manager)
{
    globus_result_t                     result;
    globus_reltime_t                    delay;

    if(manager->config->usage_disabled)
    {
        return GLOBUS_SUCCESS;
    }

    globus_i_gram_send_session_stats(manager);

    GlobusTimeReltimeSet(delay, 60*60, 0);
    result = globus_callback_register_periodic(
            &manager->usagetracker->session_timer_handle,
            &delay,
            &delay,
            globus_l_gram_kickout_session_stats,
            manager);

    return result;
}
