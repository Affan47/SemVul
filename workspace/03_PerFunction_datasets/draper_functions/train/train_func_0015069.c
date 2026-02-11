update_now (const time_t system_time)
{
  const int forward_threshold = 86400;
  const int backward_trigger  = 10;
  time_t real_time = system_time + now_adj;

  if (real_time > now)
    {
      const time_t overshoot = real_time - now - 1;
      if (overshoot > forward_threshold && now_adj >= overshoot)
        {
          now_adj -= overshoot;
          real_time -= overshoot;
        }
      now = real_time;
    }
  else if (real_time < now - backward_trigger)
    now_adj += (now - real_time);
}
