make_ipv4_socket(void) {

  if ((serve_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    write_error("Cannot create IPv4 socket for socket server\n");
    socket_error_notify();
    return false;
  }

  sockaddr_in serve_address;
  std::memset(&serve_address, 0, sizeof(serve_address));

  serve_address.sin_family = AF_INET;
  if (other_sock_client_address) serve_address.sin_addr.s_addr = htonl(INADDR_ANY);
  else {
    int res = inet_pton(AF_INET, "127.0.0.1", &(serve_address.sin_addr));
    if (res <= 0) {
      write_error("Cannot create IPv4 network address for localhost\n");
      socket_error_notify();
      return false;
    }
  }
  serve_address.sin_port = htons(std::atoi(port.c_str()));

  if ((bind(serve_sock_fd, (sockaddr*)&serve_address, sizeof(serve_address))) < 0) {
    write_error("Cannot bind to socket for socket server\n");
    socket_error_notify();
    return false;
  }

  if ((listen(serve_sock_fd, 5)) < 0) {
    write_error("Cannot listen on socket of socket server\n");
    socket_error_notify();
    return false;
  }
  return true;
}
