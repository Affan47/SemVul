ArgusProcessRemoteSocket(struct ArgusClientData *client, int fd)
{
   char buf[MAXBUFSIZE];
   int retn = 0, cnt;

   bzero (buf, sizeof(buf));

   if ((cnt = recv (fd, buf, MAXBUFSIZE, 0)) != 0) {
#ifdef ARGUSDEBUG
      ArgusDebug (3, "ArgusProcessRemoteSocket: read '%s' from remote\n", buf);
#endif
      if ((strncmp (buf, "DONE: ", 6)) == 0)
         retn = -4;

      if ((strncmp (buf, "FILTER: ", 8)) == 0) {
         if (ArgusFilterCompile (&ArgusBPFcode, &buf[7], 0, 0) < 0) {
            retn = -2;

         } else {
            ArgusFilterInitialized++;
            retn = 0;
            if (Argusbpflag)
               Argusbpf_dump (&ArgusBPFcode, Argusbpflag);

#ifdef ARGUSDEBUG
            ArgusDebug (2, "ArgusProcessRemoteSocket: ArgusFilter %s initialized.\n", &buf[7]);
#endif
         }
      }

   } else {
      close (fd);
      fd = -1;
      retn = -1;
   }

#ifdef ARGUSDEBUG
   ArgusDebug (6, "ArgusProcessRemoteSocket: returning %d\n", retn);
#endif

   return (retn);
}
