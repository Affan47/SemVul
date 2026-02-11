net_driver_wait (net_driver_t *driver, int extra_fd, int *status, float *delayed_usecs)
{
    netjack_driver_state_t *netj = &( driver->netj );
    int delay;

    delay = netjack_wait( netj, driver->engine->get_microseconds );
    if( delay ) {

	    jack_error( "netxruns amount: %dms", delay/1000 );
    }


    driver->last_wait_ust = driver->engine->get_microseconds ();
    driver->engine->transport_cycle_start (driver->engine, driver->last_wait_ust);


    *delayed_usecs = 0;
    *status = 0;
    return netj->period_size;
}
