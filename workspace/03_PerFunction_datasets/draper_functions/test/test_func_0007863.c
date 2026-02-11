step_recv (char **data)
{
  if (args_info.imap_flag)
    return imap_step_recv (data);
  if (args_info.smtp_flag)
    return smtp_step_recv (data);

  if (!readln (data))
    return 0;

  return 1;
}
