timer_is_expired(void) {
        time_t nowt = time(NULL);

        if(nowt - _timer_start_time >= _timer_limit)
                return 1;
        return 0;
}
