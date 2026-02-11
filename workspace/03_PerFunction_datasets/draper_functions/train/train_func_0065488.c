b_clear_line(buffer, number)
  Buffer *buffer;
  long number;
{
  long position = b_goto_line(buffer, number);
  long length = b_length_of_line(buffer, number);

  return b_delete(buffer, position, length ? length - 1 : 0);
}
