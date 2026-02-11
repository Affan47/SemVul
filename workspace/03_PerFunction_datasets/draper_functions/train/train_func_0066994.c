number(const char *s)
{
	if (!is_number(s))
		ash_msg_and_raise_error(msg_illnum, s);
	return atoi(s);
}
