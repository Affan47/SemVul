circuit_build_times_network_check_changed(circuit_build_times_t *cbt)
{
  int total_build_times = cbt->total_build_times;
  int timeout_count=0;
  int i;


  for (i = 0; i < cbt->liveness.num_recent_circs; i++) {
    timeout_count += cbt->liveness.timeouts_after_firsthop[i];
  }


  if (timeout_count < circuit_build_times_max_timeouts()) {
    return 0;
  }

  circuit_build_times_reset(cbt);
  memset(cbt->liveness.timeouts_after_firsthop, 0,
          sizeof(*cbt->liveness.timeouts_after_firsthop)*
          cbt->liveness.num_recent_circs);
  cbt->liveness.after_firsthop_idx = 0;


  if (cbt->timeout_ms >= circuit_build_times_get_initial_timeout()) {
    if (cbt->timeout_ms > INT32_MAX/2 || cbt->close_ms > INT32_MAX/2) {
      log_warn(LD_CIRC, "Insanely large circuit build timeout value. "
              "(timeout = %fmsec, close = %fmsec)",
               cbt->timeout_ms, cbt->close_ms);
    } else {
      cbt->timeout_ms *= 2;
      cbt->close_ms *= 2;
    }
  } else {
    cbt->close_ms = cbt->timeout_ms
                  = circuit_build_times_get_initial_timeout();
  }

  control_event_buildtimeout_set(cbt, BUILDTIMEOUT_SET_EVENT_RESET);

  log_notice(LD_CIRC,
            "Your network connection speed appears to have changed. Resetting "
            "timeout to %lds after %d timeouts and %d buildtimes.",
            tor_lround(cbt->timeout_ms/1000), timeout_count,
            total_build_times);

  return 1;
}
