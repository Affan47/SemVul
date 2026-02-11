print_statistics(FILE *o, time_t t) {
    if (show_progress != NULL) {
      (*show_progress)(o, verbose_prefix.c_str(),
                       (unsigned int)(t - first_time), Nall, Nmax,
                       (t > first_time ?
                        (((double)N) / (((t - first_time) > T) ? T :
                                        (t - first_time))) : ((double)0)),
                       (t > first_time ?
                        (((double)Nall) / (t - first_time)) : ((double)0)));
      return;
    }
    std::string::size_type outlen = verbose_prefix.length()+100;
    char* out = new char[outlen];
    if(out) try {
      snprintf(out,outlen,
            "%s%5u s: %10.1f kB  %8.1f kB/s  %8.1f kB/s    %c %c %c       ",
            verbose_prefix.c_str(),
            (unsigned int)(t - first_time),
            ((double)Nall) / 1024,
            (t > first_time ?
             (((double)N) / (((t - first_time) > T) ? T :
                             (t - first_time)) / 1024) : ((double)0)),
            (t > first_time ?
             (((double)Nall) / (t - first_time) / 1024) : ((double)0)),
            (min_speed_failed ? '!' : '.'),
            (min_average_speed_failed ? '!' : '.'),
            (max_inactivity_time_failed ? '!' : '.'));
      logger.msg(INFO, out);
    } catch(std::exception& e) { }
    delete[] out;
  }
