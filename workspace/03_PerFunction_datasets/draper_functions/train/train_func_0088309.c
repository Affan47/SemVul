echo_finish (void)
{
  ping_finish ();
  if (ping->ping_num_recv && PING_TIMING (data_length))
    {
      struct ping_stat *ping_stat = (struct ping_stat *) ping->ping_closure;
      double total = ping->ping_num_recv + ping->ping_num_rept;
      double avg = ping_stat->tsum / total;
      double vari = ping_stat->tsumsq / total - avg * avg;

      printf ("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
	      ping_stat->tmin, avg, ping_stat->tmax, nsqrt (vari, 0.0005));
    }
  return (ping->ping_num_recv == 0);
}
