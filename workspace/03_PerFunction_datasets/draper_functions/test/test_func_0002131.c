main(int argc, char* argv[]) {

  if (argc < 3) {
    error_msg("Insufficient arguments\n"
	      "Usage efax-gtk-socket-client [hostname] [port]\n");
    return 1;
  }

  struct hostent* hostname_info;
  if ((hostname_info = gethostbyname(argv[1])) == 0) {
    std::string message("Cannot get address for hostname ");
    message += argv[1];
    message += '\n';
    error_msg(message.c_str());
    return 1;
  }

  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0) {
    error_msg("Cannot create socket for socket server\n");
    return 1;
  }

  sockaddr_in address;
  std::memset(&address, 0, sizeof(address));

  address.sin_family = AF_INET;
  address.sin_addr = *(in_addr*)hostname_info->h_addr_list[0];
  address.sin_port = htons(std::atoi(argv[2]));

  if (connect(sock_fd, (sockaddr*)&address, sizeof(address)) < 0) {
    error_msg("Cannot connect to efax-gtk server socket\n");
    close(sock_fd);
    return 1;
  }

  char buffer[BUFFER_LENGTH];
  ssize_t read_result;
  ssize_t write_result = 0;
  ssize_t written;

  while ((read_result = read(0, buffer, BUFFER_LENGTH)) > 0
	 && write_result != -1) {
    written = 0;
    do {
      write_result = write(sock_fd, buffer + written, read_result);
      written += write_result;

      read_result -= write_result;
    } while (read_result && write_result != -1);
  }

  if (write_result == -1) error_msg("Write error to socket\n");

  close(sock_fd);

  return 0;
}
