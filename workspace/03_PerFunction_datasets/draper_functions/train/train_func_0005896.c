sa_update_entry(struct snmp_alarm *a)
{
    if (a->t_last.tv_sec == 0 && a->t_last.tv_usec == 0) {
        struct timeval  t_now;


        gettimeofday(&t_now, NULL);

        a->t_last.tv_sec = t_now.tv_sec;
        a->t_last.tv_usec = t_now.tv_usec;

        NETSNMP_TIMERADD(&t_now, &a->t, &a->t_next);
    } else if (a->t_next.tv_sec == 0 && a->t_next.tv_usec == 0) {


        if (a->flags & SA_REPEAT) {
            if (a->t.tv_sec == 0 && a->t.tv_usec == 0) {
                DEBUGMSGTL(("snmp_alarm",
                            "update_entry: illegal interval specified\n"));
                snmp_alarm_unregister(a->clientreg);
                return;
            }

            NETSNMP_TIMERADD(&a->t_last, &a->t, &a->t_next);
        } else {


            snmp_alarm_unregister(a->clientreg);
        }
    }
}
