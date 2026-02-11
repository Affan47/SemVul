Outro ()
{
  int             i;
  PUTHEAD (COUTRO);
  ssendallreliable (buffer, HEADSIZE);
  for (i = 0; i < connected; i++)
    conn[client].ready = 0;
}
