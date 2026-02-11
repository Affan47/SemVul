gt_timer_print_progress_report(GtTimer *t,
    struct timeval *elapsed_tv, struct timeval *elapsed_user_tv,
    struct timeval *elapsed_sys_tv, const char *desc, FILE *fp)
{
  fprintf(fp,"# TIME %s %ld.%02ld",
          desc,
          (long)(elapsed_tv->tv_sec),
          (long)(elapsed_tv->tv_usec)/10000);
  if (t->show_cpu_time) {
    fprintf(fp, " (user: %ld.%02ld; sys: %ld.%02ld)\n",
            (long)(elapsed_user_tv->tv_sec),
            (long)(elapsed_user_tv->tv_usec)/10000,
            (long)(elapsed_sys_tv->tv_sec),
            (long)(elapsed_sys_tv->tv_usec)/10000);
  }
  else {
    fprintf(fp, "\n");
  }
}
