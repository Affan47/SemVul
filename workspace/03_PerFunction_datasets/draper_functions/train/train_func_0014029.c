netUnlockDB (void)
{
  if (debug)
    {
      fprintf (stderr, "%s: writing `UNDB'\n", program_name);
    }
  fprintf (serv_write, "UNDB\r\n");
  get_reply (stdout);
}
