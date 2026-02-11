cli_cmd_await_connected (unsigned conn_timo)
{
        int32_t                 ret = 0;
        struct  timespec        ts = {0,};

        if (!conn_timo)
                return 0;

        pthread_mutex_lock (&conn_mutex);
        {
                seconds_from_now (conn_timo, &ts);
                while (!connected && !ret) {
                        ret = pthread_cond_timedwait (&conn, &conn_mutex,
                                                      &ts);
                }
        }
        pthread_mutex_unlock (&conn_mutex);


        return ret;
}
