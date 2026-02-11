print_buffer(char *buffer, size_t count)
{
  const char s[]= " ";
  for (; count && *buffer; --count)
  {
    my_write_stderr(isprint(*buffer) ? buffer : s, 1);
    ++buffer;
  }
}
