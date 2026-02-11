client_chdb (const char *newRoot)
{
  if (newRoot == NULL)
    {
      newRoot = "default";
    }


  if (debug)
    {
      fprintf (stderr, "%s: writing `CHDB %s'\n", program_name, newRoot);
    }
  fprintf (serv_write, "CHDB %s\r\n", newRoot);
  get_reply (stdout);
}
