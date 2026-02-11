realtime(time_t exptime) {
    time_t now;


    if (exptime == 0) return 0;

    if (exptime > REALTIME_MAXDELTA)
        return exptime;
    else {
        now = time(0);
        return exptime + now;
    }
}
