transfer(unsigned long long int n) {
    if (disabled) {
      last_time = time(NULL);
      return true;
    }
    time_t t = time(NULL);
    time_t dt = t - last_time;
    Nall += n;
    if (dt > T)
      N = (n * dt) / T;
    else
      N = (N * (T - dt)) / T + n;
    if ((t - first_time) >= T * 3) {


      if (N < (T * min_speed))
        if (first_speed_failure != 0) {
          if (t > (first_speed_failure + min_speed_time))
            min_speed_failed = true;
        }
        else
          first_speed_failure = t;
      else
        first_speed_failure = 0;

      if ((min_average_speed * (t - first_time)) > Nall)
        min_average_speed_failed = true;

      if (t > (last_activity_time + max_inactivity_time))
        max_inactivity_time_failed = true;
    }
    if (n > 0)
      last_activity_time = t;
    last_time = t;
    if (be_verbose)

      if ((t - last_printed) >= 1) {
        print_statistics(stderr, t);
        last_printed = t;
      }
    return !(min_speed_failed || min_average_speed_failed ||
             max_inactivity_time_failed);
  }
