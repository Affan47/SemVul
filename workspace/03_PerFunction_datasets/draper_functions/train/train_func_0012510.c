Finalize_IOType_transport_impl() {
  int index;

  for(index = 0; index < IOTypes_table.num_registered; index++) {
    if(IOTypes_table.io_def[index].direction == REG_IO_OUT) {

      cleanup_listener_connection_samples(index);
      socket_info_cleanup(&(socket_info_table.socket_info[index]));
    }
    else if(IOTypes_table.io_def[index].direction == REG_IO_IN) {

      cleanup_connector_connection_samples(index);
      socket_info_cleanup(&(socket_info_table.socket_info[index]));
    }
  }
}
