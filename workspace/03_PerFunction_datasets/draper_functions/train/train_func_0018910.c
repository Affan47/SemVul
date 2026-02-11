rate_limit_is_ready(ratelim_t *lim, time_t now)
{
  if (lim->rate + lim->last_allowed <= now) {
    int res = lim->n_calls_since_last_time + 1;
    lim->last_allowed = now;
    lim->n_calls_since_last_time = 0;
    return res;
  } else {
    ++lim->n_calls_since_last_time;
    return 0;
  }
}
