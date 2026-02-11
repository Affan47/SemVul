loader_sigchld_handler(int signum)
{
  int status;
  pid_t pid;
  struct loader_child *child_ptr;
  int signal;

  while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
  {
    child_ptr = loader_child_find_and_mark_dead(pid);

    if (!child_ptr)
    {
      log_error("Termination of unknown child process with PID %llu detected", (unsigned long long)pid);
    }
    else
    {
      log_info("Termination of child process '%s' with PID %llu detected", child_ptr->app_name, (unsigned long long)pid);
    }

    if (WIFEXITED(status))
    {
      log_info("Child exited, status=%d", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status))
    {
      signal = WTERMSIG(status);
      switch (signal)
      {
      case SIGILL:
      case SIGABRT:
      case SIGSEGV:
      case SIGFPE:
        log_error("Child was killed by signal %d", signal);
        break;
      default:
        log_info("Child was killed by signal %d", signal);
      }
    }
    else if (WIFSTOPPED(status))
    {
      log_info("Child was stopped by signal %d", WSTOPSIG(status));
    }
  }
}
