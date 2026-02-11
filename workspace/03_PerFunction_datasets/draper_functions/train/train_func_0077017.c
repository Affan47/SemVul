ev_run (EV_P_ int flags)
{
#if EV_FEATURE_API
  ++loop_depth;
#endif

  assert (("libev: ev_loop recursion during release detected", loop_done != EVBREAK_RECURSE));

  loop_done = EVBREAK_CANCEL;

  EV_INVOKE_PENDING;

  do
    {
#if EV_VERIFY >= 2
      ev_verify (EV_A);
#endif

#ifndef _WIN32
      if (expect_false (curpid))
        if (expect_false (getpid () != curpid))
          {
            curpid = getpid ();
            postfork = 1;
          }
#endif

#if EV_FORK_ENABLE

      if (expect_false (postfork))
        if (forkcnt)
          {
            queue_events (EV_A_ (W *)forks, forkcnt, EV_FORK);
            EV_INVOKE_PENDING;
          }
#endif

#if EV_PREPARE_ENABLE

      if (expect_false (preparecnt))
        {
          queue_events (EV_A_ (W *)prepares, preparecnt, EV_PREPARE);
          EV_INVOKE_PENDING;
        }
#endif

      if (expect_false (loop_done))
        break;


      if (expect_false (postfork))
        loop_fork (EV_A);


      fd_reify (EV_A);


      {
        ev_tstamp waittime  = 0.;
        ev_tstamp sleeptime = 0.;


        ev_tstamp prev_mn_now = mn_now;


        time_update (EV_A_ 1e100);

        if (expect_true (!(flags & EVRUN_NOWAIT || idleall || !activecnt)))
          {
            waittime = MAX_BLOCKTIME;

            if (timercnt)
              {
                ev_tstamp to = ANHE_at (timers [HEAP0]) - mn_now + backend_fudge;
                if (waittime > to) waittime = to;
              }

#if EV_PERIODIC_ENABLE
            if (periodiccnt)
              {
                ev_tstamp to = ANHE_at (periodics [HEAP0]) - ev_rt_now + backend_fudge;
                if (waittime > to) waittime = to;
              }
#endif


            if (expect_false (waittime < timeout_blocktime))
              waittime = timeout_blocktime;


            if (expect_false (io_blocktime))
              {
                sleeptime = io_blocktime - (mn_now - prev_mn_now);

                if (sleeptime > waittime - backend_fudge)
                  sleeptime = waittime - backend_fudge;

                if (expect_true (sleeptime > 0.))
                  {
                    ev_sleep (sleeptime);
                    waittime -= sleeptime;
                  }
              }
          }

#if EV_FEATURE_API
        ++loop_count;
#endif
        assert ((loop_done = EVBREAK_RECURSE, 1));
        backend_poll (EV_A_ waittime);
        assert ((loop_done = EVBREAK_CANCEL, 1));


        time_update (EV_A_ waittime + sleeptime);
      }


      timers_reify (EV_A);
#if EV_PERIODIC_ENABLE
      periodics_reify (EV_A);
#endif

#if EV_IDLE_ENABLE

      idle_reify (EV_A);
#endif

#if EV_CHECK_ENABLE

      if (expect_false (checkcnt))
        queue_events (EV_A_ (W *)checks, checkcnt, EV_CHECK);
#endif

      EV_INVOKE_PENDING;
    }
  while (expect_true (
    activecnt
    && !loop_done
    && !(flags & (EVRUN_ONCE | EVRUN_NOWAIT))
  ));

  if (loop_done == EVBREAK_ONE)
    loop_done = EVBREAK_CANCEL;

#if EV_FEATURE_API
  --loop_depth;
#endif
}
