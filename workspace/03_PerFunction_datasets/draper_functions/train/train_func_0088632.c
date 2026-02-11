setTimer(AuInt32 rate)
{
    AuInt32 timer_ms;
    AuInt32 foo;
    struct itimerval ntval, otval;

    if (NasConfig.DoDebug > 5) {
        osLogMsg("setTimer(rate = %d);\n", rate);
        IDENTMSG;
    }


    if (rate == 0) {
        ntval.it_value.tv_sec = ntval.it_value.tv_usec = 0;
        ntval.it_interval.tv_sec = ntval.it_interval.tv_usec = 0;
        timer_ms = 0x7fff;
    } else {
        timer_ms = (auMinibufSamples * 500) / rate;
        ntval.it_interval.tv_sec = 0;
        ntval.it_interval.tv_usec = timer_ms * 1000;
        ntval.it_value.tv_sec = 0;
        ntval.it_value.tv_usec = timer_ms * 10;
    }
    foo = setitimer(ITIMER_REAL, &ntval, &otval);

    UNIDENTMSG;

    return timer_ms;
}
