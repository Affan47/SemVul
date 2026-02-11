init_line_buffer(LINE_BUFFER *buffer,File file,ulong size,ulong max_buffer)
{
  buffer->file=file;
  buffer->bufread=size;
  buffer->max_size=max_buffer;
  if (!(buffer->buffer = (char*) my_malloc(buffer->bufread+1,
					   MYF(MY_WME | MY_FAE))))
    return 1;
  buffer->end_of_line=buffer->end=buffer->buffer;
  buffer->buffer[0]=0;
  return 0;
}
