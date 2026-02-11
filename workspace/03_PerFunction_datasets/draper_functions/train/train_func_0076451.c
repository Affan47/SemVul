rep_hist_load_bwhist_state_section(bw_array_t *b,
                                   const smartlist_t *s_values,
                                   const smartlist_t *s_maxima,
                                   const time_t s_begins,
                                   const int s_interval)
{
  time_t now = time(NULL);
  int retval = 0;
  time_t start;

  uint64_t v, mv;
  int i,ok,ok_m;
  int have_maxima = (smartlist_len(s_values) == smartlist_len(s_maxima));

  if (s_values && s_begins >= now - NUM_SECS_BW_SUM_INTERVAL*NUM_TOTALS) {
    start = s_begins - s_interval*(smartlist_len(s_values));
    if (start > now)
      return 0;
    b->cur_obs_time = start;
    b->next_period = start + NUM_SECS_BW_SUM_INTERVAL;
    SMARTLIST_FOREACH_BEGIN(s_values, const char *, cp) {
        const char *maxstr = NULL;
        v = tor_parse_uint64(cp, 10, 0, UINT64_MAX, &ok, NULL);
        if (have_maxima) {
          maxstr = smartlist_get(s_maxima, cp_sl_idx);
          mv = tor_parse_uint64(maxstr, 10, 0, UINT64_MAX, &ok_m, NULL);
          mv *= NUM_SECS_ROLLING_MEASURE;
        } else {

          mv = (v / s_interval) * NUM_SECS_ROLLING_MEASURE;
        }
        if (!ok) {
          retval = -1;
          log_notice(LD_HIST, "Could not parse value '%s' into a number.'",cp);
        }
        if (maxstr && !ok_m) {
          retval = -1;
          log_notice(LD_HIST, "Could not parse maximum '%s' into a number.'",
                     maxstr);
        }

        if (start < now) {
          time_t cur_start = start;
          time_t actual_interval_len = s_interval;
          uint64_t cur_val = 0;


          if (start + s_interval > now)
            actual_interval_len = now - start;
          cur_val = v / actual_interval_len;


          while (cur_start < start + actual_interval_len) {
            add_obs(b, cur_start, cur_val);
            ++cur_start;
          }
          b->max_total = mv;


          start += actual_interval_len;
        }
    } SMARTLIST_FOREACH_END(cp);
  }


  for (i=0; i<NUM_SECS_ROLLING_MEASURE; ++i) {
    b->obs[i] = 0;
  }
  b->total_obs = 0;

  return retval;
}
