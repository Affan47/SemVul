print_result() {
  int timeuse;
  gettimeofday(&end, NULL );
  timeuse = 1000 * ( end.tv_sec - start.tv_sec ) + (end.tv_usec - start.tv_usec) / 1000;

  if (total_finish > 0) total_time /= total_finish;

  printf("\nconnect successfully %d\n"
      "connect failed %d\n"
      "calculate %d\n"
      "calculate successfully %d\n"
      "client avg. time %d.%ds\n"
      "total time %d.%ds\n",
      conn_success_count, conn_fail_count,
      calc_count, calc_success_count,
      total_time / 1000, total_time % 1000,
      timeuse / 1000, timeuse % 1000);
}
