receiveIncomingData(bool nonBlocking) {
  char buffer[1024];
  int received = 0;

  buffer[1023] = '\0';

  string cmd;
  int msg_size;


  int idx = 0;
  int rec;
  while(true) {

    #ifndef WIN32
      if(nonBlocking) {
        rec = recv(clientsock, &buffer[idx], sizeof(char), MSG_DONTWAIT);
      } else {
        rec = recv(clientsock, &buffer[idx], sizeof(char), 0);
      }

      if(nonBlocking && (rec==0)) {
        return "";
      }
    #else

      rec = recv(clientsock, &buffer[idx], sizeof(char), 0);
    #endif

    received += rec;

    if((rec == 0) || (rec < 1)) {
      return cmd;
    }

    if(buffer[idx] == '\0') {
      break;
    }
    idx++;
  }


  msg_size = atoi(buffer) * sizeof(char);

  received = recv(clientsock, buffer, msg_size, 0);
  if(received < 0) {
    cerr << PACKAGE << ": erro ao receber dados." << endl;
    return cmd;
  } else if((received == 0) || (received < msg_size)) {

    closeSock();
    return cmd;
  }


  cmd = buffer;


  return cmd;
}
