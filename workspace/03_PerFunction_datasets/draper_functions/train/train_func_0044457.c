SMTP_eom(int sock, char smtp_mode)

{
  SockPrintf(sock,".\r\n");
  if (outlevel >= O_MONITOR)
      report(stdout, "%cMTP>. (EOM)\n", smtp_mode);


  if (smtp_mode == 'S')
      return SMTP_ok(sock, smtp_mode, TIMEOUT_EOM);
  else
      return SM_OK;
}
