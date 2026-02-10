mono_test_marshal_ansi_char_array (char *s)
{
	const char m[] = "abcdef";

	if (strncmp ("qwer", s, 4))
		return 1;

	memcpy (s, m, sizeof (m));
	return 0;
}
