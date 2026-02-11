sim_print_stats(FILE *fd)
{
#if 0
  extern char etext, *sbrk(int);
#endif

  if (!running)
    return;


  sim_end_time = time((time_t *)NULL);
  sim_elapsed_time = MAX(sim_end_time - sim_start_time, 1);

#if 0

  sim_mem_usage = (sbrk(0) - &etext) / 1024;
#endif


  fprintf(fd, "\nsim: ** simulation statistics **\n");
  stat_print_stats(sim_sdb, fd);
  sim_aux_stats(fd);
  fprintf(fd, "\n");
}
