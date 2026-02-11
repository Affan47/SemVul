state_check_main(void *arg)
{
    int oldstate = STATE_OFFLINE;

    while (oldstate != STATE_EXITING)
    {
        sleep(SLEEP_SHORT);


        if (
            !state_force_offline
            && is_running(discofs_options.pid_file)
            && is_reachable(discofs_options.host)
            && is_mounted(discofs_options.remote_root)
           )
         {

            state_set(STATE_ONLINE, &oldstate);

            if (oldstate == STATE_OFFLINE)
                worker_wakeup();
        }
        else
        {
            state_set(STATE_OFFLINE, &oldstate);
        }
    }

    return NULL;
}
