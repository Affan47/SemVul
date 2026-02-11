read(void *data, size_t size)
{
  if (buffer_pos >= buffer_size) {
    if (size >= sizeof(buffer)) {

      size = data_pool->get_data(data, position, size);
      position += size;
      return size;
    } else {

      buffer_size = data_pool->get_data(buffer, position, sizeof(buffer));
      buffer_pos=0;
    }
  }
  if (buffer_pos + size >= buffer_size)
    size = buffer_size - buffer_pos;
  memcpy(data, buffer+buffer_pos, size);
  buffer_pos += size;
  position += size;
  return size;
}
