maybe_another_chronyd_running(int *other_pid)
{
  const char *pidfile = CNF_GetPidFile();
  FILE *in;
  int pid, count;

  *other_pid = 0;

  in = fopen(pidfile, "r");
  if (!in) return 0;

  count = fscanf(in, "%d", &pid);
  fclose(in);

  if (count != 1) return 0;

  *other_pid = pid;
  return does_process_exist(pid);

}
