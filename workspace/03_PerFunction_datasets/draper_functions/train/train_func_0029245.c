stuff_string_white(char *outstr, int len)
{
	if(!len)
		len = NAME_LENGTH-1;

	ignore_white_space();
	copy_to_next_white(outstr, Mp, len);
	advance_to_next_white();
}
