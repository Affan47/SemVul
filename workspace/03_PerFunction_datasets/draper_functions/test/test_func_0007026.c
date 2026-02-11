globus_callback_has_time_expired(void)
{
    if (globus_i_am_only_thread())
    {
        return globus_callback_has_time_expired_nothreads();
    }
    else
    {
        return globus_callback_has_time_expired_threads();
    }
}
