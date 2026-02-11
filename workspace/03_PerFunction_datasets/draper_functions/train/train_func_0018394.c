dns_timer_execute()
{
    dns_timer_t *t;
    struct timeval now;

    gettimeofday(&now, NULL);

    while ((t = TimerHead) != NULL) {
        if (timer_tvcompare(&now, &t->t_time) < 0)
            return;

        timer_unregister(t);
        if (t->t_func != NULL)
            t->t_func(t->t_param);
    }
}
