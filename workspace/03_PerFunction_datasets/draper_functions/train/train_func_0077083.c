exhcmd_rewind(struct he_s *hedit, char *args)

{
  char *ab = alternate_buffer;
  char *skip;

  skip = exh_skipcmd(args, 0);
  alternate_buffer = current_buffer->hedit->buffer_name;
  if (he_select_buffer_(buffer_list)) {
    he_message(1, "@AbINTERNAL ERROR@~");
    he_select_buffer_(current_buffer);
    alternate_buffer = ab;
  } else {
    he_status_message(1);
    he_refresh_part(current_buffer->hedit, 0, -1);
  }
  return skip;
}
