handle_unix_request (int ls)
{
  int s;
  socklen_t len = sizeof (struct sockaddr_un);
  struct sockaddr_un server;

  server.sun_family = AF_UNIX;

  if ((s = accept(ls,(struct sockaddr *)&server, &len)) < 0)
    {
      perror(progname);
      fprintf(stderr,"%s: unable to accept\n",progname);
    }

  echo_request(s);

}
