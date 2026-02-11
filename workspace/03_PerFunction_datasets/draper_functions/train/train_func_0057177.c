create_connector_samples(const int index) {

  int i;
  int yes = 1;
  int connector;
  struct sockaddr_in myAddr;


  connector = socket(AF_INET, SOCK_STREAM, 0);
  if(connector == REG_SOCKETS_ERROR) {

    perror("socket");
    socket_info_table.socket_info[index].comms_status=REG_COMMS_STATUS_FAILURE;
    return REG_FAILURE;
  }

  socket_info_table.socket_info[index].connector_handle = connector;


  if(setsockopt(connector, SOL_SOCKET, SO_REUSEADDR, &yes,
		sizeof(int)) == REG_SOCKETS_ERROR) {
    perror("setsockopt");
    return REG_FAILURE;
  }


  myAddr.sin_family = AF_INET;
  if(strlen(socket_info_table.socket_info[index].tcp_interface) == 1) {
    myAddr.sin_addr.s_addr = INADDR_ANY;
  }
  else {
    if( !inet_aton(socket_info_table.socket_info[index].tcp_interface,
		   &(myAddr.sin_addr)) ){
      fprintf(stderr, "STEER: create_connector: inet_aton failed "
	      "for interface >>%s<<\n",
	      socket_info_table.socket_info[index].tcp_interface);
      return REG_FAILURE;
    }
  }
  memset(&(myAddr.sin_zero), '\0', 8);


  if((i = socket_info_table.socket_info[index].min_port_out)) {
    myAddr.sin_port = htons((short) i);

    fprintf(stderr, "STEER: create_connector: using range %d -- %d for bind\n",
	    socket_info_table.socket_info[index].min_port_out,
	    socket_info_table.socket_info[index].max_port_out);

    while(bind(connector, (struct sockaddr*) &myAddr,
	       sizeof(struct sockaddr)) == REG_SOCKETS_ERROR) {
      if(++i > socket_info_table.socket_info[index].max_port_out) {
	fprintf(stderr, "STEER: create_connector: failed to find free local port to "
		"bind to in range %d -- %d\n",
		socket_info_table.socket_info[index].min_port_out,
		socket_info_table.socket_info[index].max_port_out);
	close(connector);
	socket_info_table.socket_info[index].comms_status=REG_COMMS_STATUS_FAILURE;
	return REG_FAILURE;
      }
      myAddr.sin_port = htons((short) i);
    }
  }
  socket_info_table.socket_info[index].comms_status=REG_COMMS_STATUS_WAITING_TO_CONNECT;


  connect_connector_samples(index);

  return REG_SUCCESS;
}
