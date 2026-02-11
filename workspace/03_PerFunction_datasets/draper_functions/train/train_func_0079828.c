add_undo_redirect (fd, ri, fdbase)
     int fd;
     enum r_instruction ri;
     int fdbase;
{
  int new_fd, clexec_flag;
  REDIRECT *new_redirect, *closer, *dummy_redirect;
  REDIRECTEE sd;

  new_fd = fcntl (fd, F_DUPFD, (fdbase < SHELL_FD_BASE) ? SHELL_FD_BASE : fdbase+1);
  if (new_fd < 0)
    new_fd = fcntl (fd, F_DUPFD, SHELL_FD_BASE);

  if (new_fd < 0)
    {
      sys_error (_("redirection error: cannot duplicate fd"));
      return (-1);
    }

  clexec_flag = fcntl (fd, F_GETFD, 0);

  sd.dest = new_fd;
  rd.dest = 0;
  closer = make_redirection (sd, r_close_this, rd, 0);
  closer->flags |= RX_INTERNAL;
  dummy_redirect = copy_redirects (closer);

  sd.dest = fd;
  rd.dest = new_fd;
  if (fd == 0)
    new_redirect = make_redirection (sd, r_duplicating_input, rd, 0);
  else
    new_redirect = make_redirection (sd, r_duplicating_output, rd, 0);
  new_redirect->flags |= RX_INTERNAL;
  if (clexec_flag == 0 && fd >= 3 && new_fd >= SHELL_FD_BASE)
    new_redirect->flags |= RX_SAVCLEXEC;
  new_redirect->next = closer;

  closer->next = redirection_undo_list;
  redirection_undo_list = new_redirect;


  add_exec_redirect (dummy_redirect);


  if (fd >= SHELL_FD_BASE && ri != r_close_this && clexec_flag)
    {
      sd.dest = fd;
      rd.dest = new_fd;
      new_redirect = make_redirection (sd, r_duplicating_output, rd, 0);
      new_redirect->flags |= RX_INTERNAL;

      add_exec_redirect (new_redirect);
    }


  if (clexec_flag || fd < 3)
    SET_CLOSE_ON_EXEC (new_fd);
  else if (redirection_undo_list->flags & RX_SAVCLEXEC)
    SET_CLOSE_ON_EXEC (new_fd);

  return (0);
}
