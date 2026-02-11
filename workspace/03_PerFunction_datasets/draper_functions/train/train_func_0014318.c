calculate_device_position(void)
{
  struct timeval now;
  gettimeofday(&now, NULL);

  timersub(&now, &start_time_rep, &time_since_start_rep);
}
