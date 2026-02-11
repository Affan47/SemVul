sentinelCheckTiltCondition(void) {
    mstime_t now = mstime();
    mstime_t delta = now - sentinel.previous_time;

    if (delta < 0 || delta > SENTINEL_TILT_TRIGGER) {
        sentinel.tilt = 1;
        sentinel.tilt_start_time = mstime();
        sentinelEvent(REDIS_WARNING,"+tilt",NULL,"#tilt mode entered");
    }
    sentinel.previous_time = mstime();
}
