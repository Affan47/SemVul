close_listener_handle_samples(const int index) {
  if(close(socket_info_table.socket_info[index].listener_handle) == REG_SOCKETS_ERROR) {
    perror("close");
    socket_info_table.socket_info[index].listener_status = REG_COMMS_STATUS_FAILURE;
  }
  else {
#ifdef REG_DEBUG
    fprintf(stderr, "STEER: close_listener_handle: close OK\n");
#endif
    socket_info_table.socket_info[index].listener_status = REG_COMMS_STATUS_NULL;
  }
}
