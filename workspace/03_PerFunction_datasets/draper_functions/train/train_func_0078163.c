service_mysql(char *ip, int sp, unsigned char options, char *miscptr, FILE * fp, int port) {
  int run = 1, next_run = 1, sock = -1;
  int myport = PORT_MYSQL;

  hydra_register_socket(sp);
  if (memcmp(hydra_get_next_pair(), &HYDRA_EXIT, sizeof(HYDRA_EXIT)) == 0)
    return;
  while (1) {
    switch (run) {
    case 1:
      if (sock >= 0) {
        hydra_mysql_send_com_quit(sock);
        sock = hydra_disconnect(sock);
      }

      if ((options & OPTION_SSL) == 0) {
        if (port != 0)
          myport = port;
        sock = hydra_connect_tcp(ip, myport);
        port = myport;
      }
      if (sock < 0) {
        if (quiet != 1) fprintf(stderr, "[ERROR] Child with pid %d terminating, can not connect\n", (int) getpid());
        hydra_child_exit(1);
      }
      next_run = 2;
      break;
    case 2:
      next_run = start_mysql(sock, ip, port, options, miscptr, fp);
      break;
    case 3:
      if (sock >= 0) {
        hydra_mysql_send_com_quit(sock);
        sock = hydra_disconnect(sock);
      }
      hydra_child_exit(0);
      return;
    default:
      fprintf(stderr, "[ERROR] Caught unknown return code, exiting!\n");
      hydra_child_exit(2);
    }
    run = next_run;
  }
}
