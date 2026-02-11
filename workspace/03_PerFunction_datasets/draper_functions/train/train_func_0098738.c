spk_s2uchar(char *start, char *dest)
{
	int val;

	val = simple_strtoul(skip_spaces(start), &start, 10);
	if (*start == ',')
		start++;
	*dest = (u_char)val;
	return start;
}
