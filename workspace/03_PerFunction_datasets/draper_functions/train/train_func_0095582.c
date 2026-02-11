find_cmd_start (start)
     int start;
{
  register int s, os;

  os = 0;
  while (((s = skip_to_delim (rl_line_buffer, os, COMMAND_SEPARATORS, SD_NOJMP|SD_NOSKIPCMD)) <= start) &&
	 rl_line_buffer[s])
    os = s+1;
  return os;
}
