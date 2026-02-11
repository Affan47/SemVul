read_psres_line(Slurper &slurper, int *equals_pos)
{
  if (equals_pos) *equals_pos = -1;

  char *s = slurper.next_line();
  if (!s) return false;

  bool is_terminator = s[0] == '.';
  unsigned len, pos = 0, last_escape = ~0;
  bool found_eq = false;

  while (true) {
    len = slurper.cur_line_length();
    if (len == 0) break;


    for (; pos < len - 1; pos++) {
      if (s[pos] == '\\') {

	pos++;
	last_escape = pos;
      } else if (!found_eq && s[pos] == '=') {

	if (equals_pos) *equals_pos = pos;
	found_eq = true;
      } else if (s[pos] == '%') {

	len = pos;
	goto done;
      }
    }


    if (pos == len || s[pos] != '\\') break;

    slurper.shorten_line(pos);
    s = slurper.append_next_line();
  }

  if (pos < len && !found_eq && s[pos] == '=' && equals_pos)
    *equals_pos = pos;

 done:


  for (pos = len; pos > 0 && (s[pos-1] == ' ' || s[pos-1] == '\t'); pos--)
    ;
  if (pos == last_escape)
    pos++;
  slurper.shorten_line(pos);
  return !is_terminator;
}
