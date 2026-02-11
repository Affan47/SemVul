eci_ready_r(eci_handle_t ptr)
{
  struct eci_internal* eci_rep = (struct eci_internal*)ptr;

  if (!ptr)
    return 0;

  if (eci_rep->pid_of_child_rep <= 0 ||
      eci_rep->cmd_read_fd_rep < 0 ||
      eci_rep->cmd_write_fd_rep < 0)
    return 0;

  return 1;
}
