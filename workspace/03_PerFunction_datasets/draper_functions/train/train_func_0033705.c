check_to_time_max( time_t (*to_time)(struct tm *), const char *func_name,
                          struct tm * (*to_date)(const time_t *) )
{
    time_t round_trip;
    time_t time        = Time_Max;
    time_t good_time   = 0;
    struct tm *date;
    struct tm *good_date = malloc(sizeof(struct tm));
    time_t time_change = Time_Max;


    do {
        printf("# Trying %s(%.0f) max...", func_name, my_difftime(time, Time_Zero));
        date = (*to_date)(&time);
        round_trip = (*to_time)(date);

        time_change /= 2;


        if(time != round_trip) {
            printf(" failed\n");
            time -= time_change;
        }
        else {
            printf(" success\n");
            good_time = time;
            memcpy(good_date, date, sizeof(struct tm));
            time += time_change;
        }
    } while(time_change > 0 && good_time < Time_Max);

    return(good_date);
}
