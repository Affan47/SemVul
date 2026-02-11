scheduleBringSlavesUpToMin(EventSelector *es)
{
    struct timeval t;


    if (minScheduled) return;

    minScheduled = 1;
    t.tv_usec = 0;
    t.tv_sec = Settings.slewTime;
    Event_AddTimerHandler(es, t, bringSlavesUpToMin, NULL);
}
