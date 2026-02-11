main(int argc, char **argv) {

  InputParams inputParams;
  struct pollfd pollfd;
  int udpSocket;
  char buffer[BUFFER_LENGTH];
  int bytes, byteCount, timeout, output;
  time_t currentSecond, startSecond;


  inputParams = parseCommand(argc, argv);


  udpSocket = openSocket(inputParams);


  if ((startSecond = time(NULL)) < 0) {
    perror("time");
    exit(EXIT_FAILURE);
  }


  byteCount = 0;
  pollfd.fd = udpSocket;
  pollfd.events = POLLIN | POLLPRI;
  timeout = (inputParams.hasTimeout) ? inputParams.timeout * 1000 : -1;

  output = (inputParams.hasOutput) ? inputParams.outputFile : 1;

  do {

    if (poll(&pollfd, 1, timeout) < 0) {
      perror("poll");
      exit(EXIT_FAILURE);
    }


    if (pollfd.revents & (POLLIN | POLLPRI)) {

      if ((bytes = recv(udpSocket, buffer, BUFFER_LENGTH, 0)) < 0) {
	perror("recv");
	exit(EXIT_FAILURE);
      }
      writeBytes(buffer, bytes, output);
      byteCount += bytes;
    }


    if (inputParams.hasTimeout) {
      if ((currentSecond = time(NULL)) < 0) {
	perror("time");
	exit(EXIT_FAILURE);
      }
      timeout = (inputParams.timeout - (currentSecond - startSecond)) * 1000;
    }
  } while (!inputParams.hasTimeout || timeout > 0);

  fprintf(stderr, "Read %i bytes\n", byteCount);

  close(udpSocket);
  return EXIT_SUCCESS;
}
