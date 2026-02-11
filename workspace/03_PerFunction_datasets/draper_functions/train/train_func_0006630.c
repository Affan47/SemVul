list_retrieve_callback(void* arg,globus_ftp_control_handle_t*,globus_object_t *error,globus_byte_t* ,globus_size_t ,globus_off_t ,globus_bool_t ) {
  GridFTP_Commands *it = (GridFTP_Commands*)arg;
  globus_mutex_lock(&(it->data_lock));
  it->last_action_time=time(NULL);
  if(it->check_abort(error)) {
    it->free_data_buffer();
    globus_mutex_unlock(&(it->data_lock));
    return;
  };
  globus_bool_t eodf;
  globus_size_t size;
  if(it->dir_list_pointer == it->dir_list.end()) {
    it->virt_offset=0;
    it->transfer_mode=false;
    it->free_data_buffer();
    logger.msg(Arc::VERBOSE, "Closing channel (list)");
    it->send_response("226 Transfer completed.\r\n");
    globus_mutex_unlock(&(it->data_lock));
    return;
  };
  globus_ftp_control_local_send_eof(&(it->handle),GLOBUS_TRUE);
  ++(it->dir_list_pointer);
  if(it->dir_list_pointer == it->dir_list.end()) {
    size=0; eodf=GLOBUS_TRUE;
  }
  else {
    size=make_list_string(*(it->dir_list_pointer),it->list_mode,
                        it->data_buffer[0].data,it->data_buffer_size,
                        it->list_name_prefix.c_str());
    eodf=GLOBUS_FALSE;
  };
  globus_result_t res;
  res=globus_ftp_control_data_write(&(it->handle),
                   (globus_byte_t*)(it->data_buffer[0].data),
                   size,it->list_offset,eodf,
                   &list_retrieve_callback,it);
  if(res != GLOBUS_SUCCESS) {
    it->free_data_buffer();
    it->force_abort();
    globus_mutex_unlock(&(it->data_lock));
    return;
  };
  globus_mutex_unlock(&(it->data_lock));
}
