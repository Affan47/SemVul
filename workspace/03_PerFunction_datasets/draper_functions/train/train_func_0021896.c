strip_hex(char *line)
{
	if (STRNEQ(line, "0x"))
		shift_string_left(line, 2);

	return(line);
}
