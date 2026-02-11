create_pidfile(int num)
{
  FILE *pidfile = NULL;
  char name[32];

  if (num < 0) return -1;

  snprintf(name, 32, "/var/run/br2684ctl-nas%d.pid", num);
  pidfile = fopen(name, "w");
  if (pidfile == NULL) return -1;
  fprintf(pidfile, "%d", getpid());
  fclose(pidfile);

  return 0;
}
