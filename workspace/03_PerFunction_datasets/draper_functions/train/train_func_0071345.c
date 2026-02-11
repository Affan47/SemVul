spos (int client, unsigned char *message, int s)
{
  if (conn[client].ready)
    {
      int             x;
      GETCHAR (message, x);

      conn[client].dispframes = x * 2;
      conn[client].allframes = 25 * 2;
      conn[client].sentframes = 0;
    }
}
