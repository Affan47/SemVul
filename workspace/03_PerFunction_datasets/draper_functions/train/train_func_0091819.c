init_server (void)
{
  if ((Socket = CreateDgramSocket (initport)) == -1)
    {
      error ("Could not create Dgram socket");
      exit (-1);
    }
  printf ("Initializing koules network server at port: %i\n", initport);
  if (SetSocketNonBlocking (Socket, 1) == -1)
    {
      error ("Can't make contact socket non-blocking");
      exit (-1);
    }

  SetTimeout (0, 0);
}
