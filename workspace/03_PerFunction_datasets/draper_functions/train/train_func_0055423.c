attempt_connector_connect_samples(const int index) {
  socket_info_type *socket_info;
  socket_info = &(socket_info_table.socket_info[index]);

  if(socket_info->comms_status == REG_COMMS_STATUS_WAITING_TO_CONNECT) {
#ifdef REG_DEBUG
    fprintf(stderr, "STEER: attempt_connector_connect: poll_socket\n");
#endif
    poll_socket_samples(index);
  }

  if(socket_info->comms_status == REG_COMMS_STATUS_FAILURE ||
     socket_info->comms_status == REG_COMMS_STATUS_NULL) {

#ifdef REG_DEBUG
    fprintf(stderr, "STEER: attempt_connector_connect: retry connect\n");
#endif
    retry_connect_samples(index);
  }
}
