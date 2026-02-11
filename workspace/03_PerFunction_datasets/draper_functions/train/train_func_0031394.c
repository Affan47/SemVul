s(const char* name, const char* value)
{
  obuf_puts(&outbuf, name);
  obuf_puts(&outbuf, (value == 0) ? "(null)" : value);
  obuf_putc(&outbuf, '\n');
}
