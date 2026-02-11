glob_meters(void *dummy, t_float f)
{
    if (f == 0)
        sys_getmeters(0, 0);
    sched_meterson = (f != 0);
    sched_lastinclip = sched_lastoutclip = sched_lastindb = sched_lastoutdb =
        -1;
}
