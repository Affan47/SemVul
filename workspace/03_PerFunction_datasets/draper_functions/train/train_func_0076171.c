jsparser_buffer_absolute_pos(jsparser_ctx *js, int pos)
{
  int absolute_pos;
  int buffer_len;
  assert(pos < 0);

  if(pos <= -JSPARSER_RING_BUFFER_SIZE) {
    return -1;
  }

  buffer_len = js->buffer_end - js->buffer_start;
  if (buffer_len < 0) {
    buffer_len += JSPARSER_RING_BUFFER_SIZE;
  }

  if (pos < -buffer_len) {
    return -1;
  }

  absolute_pos = (pos + js->buffer_end) % JSPARSER_RING_BUFFER_SIZE;
  if (absolute_pos < 0) {
    absolute_pos += JSPARSER_RING_BUFFER_SIZE;
  }

  return absolute_pos;
}
