is_shift (const gchar *string)
{
  return ((string[0] == '<') &&
	  (string[1] == 's' || string[1] == 'S') &&
	  (string[2] == 'h' || string[2] == 'H') &&
	  (string[3] == 'i' || string[3] == 'I') &&
	  (string[4] == 'f' || string[4] == 'F') &&
	  (string[5] == 't' || string[5] == 'T') &&
	  (string[6] == '>'));
}
