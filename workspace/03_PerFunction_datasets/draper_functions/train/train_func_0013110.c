help_server(char *dest_path, int defaultPort) {
  int returncode = 0;
  char adr_prox[HTS_URLMAXSIZE * 2];
  int port_prox;
  T_SOC soc = smallserver_init_std(&port_prox, adr_prox, defaultPort);

  if (soc != INVALID_SOCKET) {
    char url[HTS_URLMAXSIZE * 2];
    char method[32];
    char data[32768];

    url[0] = method[0] = data[0] = '\0';

    printf("Okay, temporary server installed.\nThe URL is:\n");
    printf("URL=http://%s:%d/\n", adr_prox, port_prox);
#ifndef _WIN32
    {
      pid_t pid = getpid();

      printf("PID=%d\n", (int) pid);
    }
#endif
    fflush(stdout);
    fflush(stderr);

    if (!smallserver(soc, url, method, data, dest_path)) {
      int last_errno = errno;

      fprintf(stderr, "Unable to create the server: %s\n",
              strerror(last_errno));
#ifdef _WIN32
      closesocket(soc);
#else
      close(soc);
#endif
      printf("Done\n");
      returncode = 1;
    } else {
      returncode = 0;
    }
  } else {
    fprintf(stderr,
            "Unable to initialize a temporary server (no remaining port)\n");
    returncode = 1;
  }
  printf("EXITED\n");
  fflush(stdout);
  fflush(stderr);
  return returncode;
}
