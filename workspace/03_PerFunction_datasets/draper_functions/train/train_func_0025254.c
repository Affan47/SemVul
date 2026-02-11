callback()
  {
    guint64 system_time;
    guint64 simulation_time;
    guint64 diff_us;
    struct timeval tv;


    gettimeofday(&tv,0);

    system_time = (tv.tv_sec-tv_start.tv_sec)*1000000ULL+(tv.tv_usec-tv_start.tv_usec);

    simulation_time = ((get_cycles().get()-cycle_start)*4.0e6*cpu->get_OSCperiod());


    if( simulation_time > system_time)
    {


	diff_us = simulation_time - system_time;

	if(period > diff_us)
          period -= diff_us;
        else
          period=1;
        usleep((unsigned int)diff_us);
    }
    else
    {
	diff_us = system_time - simulation_time;

	period+=diff_us;

        if(period>1000000)
            period=1000000;

        if(diff_us>1000000)
        {

            if(warntimer<10)
                warntimer++;
            else
            {
                warntimer=0;
                puts("Processor is too slow for realtime mode!");
            }
        }
        else
            warntimer=0;
    }

    guint64 delta_cycles= (guint64)(period*cpu->get_frequency()/4000000);
    if(delta_cycles<1)
      delta_cycles=1;


    if(realtime_mode_with_gui)
    {
        update_gui();
    }

#ifdef REALTIME_DEBUG
    if(tv.tv_sec<stat_start.tv_sec+10) {
      diffsum+=diff_us;
      diffsumct++;
    }
    else
    {
      dump_stats();
    }
    if(diff_us>diffmax)
      diffmax=diff_us;

    static guint64 oldtime = 0;

    oldtime = system_time;
#endif

    guint64 fc = get_cycles().get() + delta_cycles;

    if(future_cycle)
      get_cycles().reassign_break(future_cycle, fc, this);
    else
      get_cycles().set_break(fc, this);

    future_cycle = fc;

  }
