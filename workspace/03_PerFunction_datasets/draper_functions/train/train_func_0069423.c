clear_buffer(void)
{
  if(clear_func != NULL)
    clear_func();

  if(buffer == NULL)
    return;

  overlapped = 0;
  memset(buffer, 0, BUFFER_SIZE);
  current_buffer = buffer;
  pointer = 0;
  cr_received = 0;
}
