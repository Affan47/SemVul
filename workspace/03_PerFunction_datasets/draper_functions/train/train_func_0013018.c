net_socket(int family) {
  int sock, param;


  sock = socket(family, SOCK_STREAM, IPPROTO_TCP);
  if (sock == -1) {
    syscall_fail("socket", 0, 0);
    return -1;
  }


  param = 1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *)&param, sizeof(int))) {
    syscall_fail("setsockopt", "SO_REUSEADDR", 0);
    close(sock);
    return -1;
  }

  net_create(&sock);
  return sock;
}
