send_command(mailpop3 * f, char * command)
{
  ssize_t r;

  r = mailstream_write(f->pop3_stream, command, strlen(command));
  if (r == -1)
    return -1;

  r = mailstream_flush(f->pop3_stream);
  if (r == -1)
    return -1;

  return 0;
}
