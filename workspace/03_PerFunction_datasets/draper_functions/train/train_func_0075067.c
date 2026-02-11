check_output (char const *outfile)
{
  if (outfile)
    {
      int outfd = open (outfile, O_WRONLY | O_CREAT | O_BINARY, MODE_RW_UGO);
      if (outfd < 0)
        die (_("open failed"), outfile);
      move_fd_or_die (outfd, STDOUT_FILENO);
    }
}
