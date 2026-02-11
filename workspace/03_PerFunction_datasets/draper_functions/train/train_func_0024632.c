gpg_agent_runtime_change (void)
{
#ifndef HAVE_W32_SYSTEM
  char *agent = getenv ("GPG_AGENT_INFO");
  char *pid_str;
  unsigned long pid_long;
  char *tail;
  pid_t pid;

  if (!agent)
    return;

  pid_str = strchr (agent, ':');
  if (!pid_str)
    return;

  pid_str++;
  errno = 0;
  pid_long = strtoul (pid_str, &tail, 0);
  if (errno || (*tail != ':' && *tail != '\0'))
    return;

  pid = (pid_t) pid_long;


  if (pid_long != (unsigned long) pid)
    return;


  kill (pid, SIGHUP);
#else
  gpg_error_t err;
  const char *pgmname;
  const char *argv[2];
  pid_t pid;

  pgmname = gnupg_module_name (GNUPG_MODULE_NAME_CONNECT_AGENT);
  argv[0] = "reloadagent";
  argv[1] = NULL;

  err = gnupg_spawn_process_fd (pgmname, argv, -1, -1, -1, &pid);
  if (!err)
    err = gnupg_wait_process (pgmname, pid, NULL);
  if (err)
    gc_error (0, 0, "error running `%s%s': %s",
              pgmname, " reloadagent", gpg_strerror (err));
#endif
}
