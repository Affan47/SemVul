H5_timer_end (H5_timer_t *sum, H5_timer_t *timer)
{
    H5_timer_t		now;

    HDassert(timer);
    H5_timer_begin(&now);

    timer->utime = MAX(0.0F, now.utime - timer->utime);
    timer->stime = MAX(0.0F, now.stime - timer->stime);
    timer->etime = MAX(0.0F, now.etime - timer->etime);

    if (sum) {
        sum->utime += timer->utime;
        sum->stime += timer->stime;
        sum->etime += timer->etime;
    }
}
