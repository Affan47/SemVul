_check_viewedit_process_status (gftp_viewedit_data * ve_proc, int ret)
{
  int procret;

  if (WIFEXITED (ret))
    {
      procret = WEXITSTATUS (ret);
      if (procret != 0)
        {
          ftp_log (gftp_logging_error, NULL,
                   _("Error: Child %d returned %d\n"), ve_proc->pid, procret);
          if (ve_proc->view)
            remove_file (ve_proc);

          return (0);
        }
      else
        {
          ftp_log (gftp_logging_misc, NULL,
                   _("Child %d returned successfully\n"), ve_proc->pid);
          return (1);
        }
    }
  else
    {
      ftp_log (gftp_logging_error, NULL,
               _("Error: Child %d did not terminate properly\n"),
               ve_proc->pid);
      return (0);
    }
}
