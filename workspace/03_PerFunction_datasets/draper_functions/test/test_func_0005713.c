get_next_alarm_delay_time(struct timeval *delta)
{
    struct snmp_alarm *sa_ptr;
    struct timeval  t_now;

    sa_ptr = sa_find_next();

    if (sa_ptr) {
        gettimeofday(&t_now, NULL);

        if (timercmp(&t_now, &sa_ptr->t_next, >)) {


            delta->tv_sec = 0;
            delta->tv_usec = 1;
            return sa_ptr->clientreg;
        } else {


            NETSNMP_TIMERSUB(&sa_ptr->t_next, &t_now, delta);

            return sa_ptr->clientreg;
        }
    }


    return 0;
}
