netLockPR (const char *prNum, const char *username, const char *processID)
{
  if (processID != NULL)
    {
      fprintf (serv_write, "LOCK %s %s %s\r\n", prNum, username, processID);
    }
  else
    {
      fprintf (serv_write, "LOCK %s %s\r\n", prNum, username);
    }
  get_reply (stdout);
}
