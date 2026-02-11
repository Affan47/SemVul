ArgusCheckClientStatus ()
{
   int retn, fd;
   struct sockaddr from;
   int len = sizeof (from);

   if ((fd = accept (ArgusLfd, (struct sockaddr *)&from, &len)) > 0) {
      if ((fcntl (fd, F_SETFL, O_NONBLOCK)) >= 0) {
         if (ArgusTcpWrapper (fd, &from) >= 0) {
            int i;
            for (i = 0; i < ARGUS_MAXLISTEN; i++) {
               if (ArgusOutputTask->client[i].pid == -1) {
                  if ((retn = pipe(ArgusOutputTask->client[i].pipe)) == 0) {
                     pid_t pid;

                     ArgusOutputTask->clienttags |= (1 << i);
                     ArgusOutputTask->client[i].fd = fd;

                     if ((ArgusOutputTask->client[i].sock = ArgusNewSocket (ArgusOutputTask->client[i].pipe[CLIENTSIDE])) != NULL) {
                        bcopy ((char *)&from, (char *)&ArgusOutputTask->client[i].sock->sock, sizeof (struct sockaddr));

                        if ((pid = fork()) != 0) {
                           ArgusOutputTask->client[i].pid = pid;
                           ArgusSendInitialMar(ArgusOutputTask->client[i].pipe[CLIENTSIDE]);

                        } else {
                           ArgusOutputTask->client[i].pid = getpid();
                           ArgusClientProcess(&ArgusOutputTask->client[i], NULL);
                           _exit(0);
                        }

                     } else
                        ArgusLog (LOG_ERR, "ArgusCheckClientStatus() ArgusNewSocket returned %s", strerror(errno));

                     break;

                  } else {
                     close (fd);
                     break;
                  }
               } else {
                  int status;

                  waitpid(ArgusOutputTask->client[i].pid, &status, WNOHANG);
                  if ((retn = kill(ArgusOutputTask->client[i].pid, 0)) < 0) {
                     ArgusCloseSocket(i);
                     i--;
                  }
               }
            }

            if (i == ARGUS_MAXLISTEN) {
               ArgusGenerateClosingMar(ARGUS_ERROR);
               ArgusSystemMar->ahdr.status |= ARGUS_MAXLISTENEXCD;
               ArgusSendOutputData(fd, ArgusSystemMar);
               close(fd);
            }

         } else
            close (fd);

      } else {
         ArgusLog (LOG_WARNING, "ArgusCheckClientStatus: fcntl: %s", strerror(errno));
         close (fd);
      }
   } else {
      ArgusLog (LOG_WARNING, "ArgusCheckClientStatus: accept: %s", strerror(errno));
      close (fd);
   }

#ifdef ARGUSDEBUG
   ArgusDebug (2, "ArgusCheckClientStatus() returning\n");
#endif
}
