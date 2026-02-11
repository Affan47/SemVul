allocate_data_buffer(void) {
  free_data_buffer();
  data_buffer=(data_buffer_t*)malloc(sizeof(data_buffer_t)*data_buffer_num);
  if(data_buffer == NULL) return false;
  unsigned int i;
  for(i = 0;i<data_buffer_num;i++) {
    data_buffer[i].used=0;
    data_buffer[i].data=(unsigned char*)malloc(data_buffer_size);
    if(data_buffer[i].data == NULL) {
      logger.msg(Arc::ERROR, "Failed to allocate memory for buffer");
      break;
    };
  };
  if(i == 0) {
    free(data_buffer); data_buffer=NULL; return false;
  };
  logger.msg(Arc::VERBOSE, "Allocated %u buffers %llu bytes each.", i, data_buffer_size);
  data_buffer_num=i;
  return true;
}
