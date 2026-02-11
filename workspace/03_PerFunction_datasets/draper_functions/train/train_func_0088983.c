parse_file_cmd( const char *filecmdstr, char **retval)
{
	int start = 0, idx, hack = 0;


	while (isspace(filecmdstr[start]))
		start++;
	idx = start;
	while (filecmdstr[idx] && filecmdstr[idx] != '\n')
		idx++;


	if (filecmdstr[idx] == '\n')
		hack = 1;
	if (idx == start)
		bb_error_msg_and_die("empty filename");
	*retval = xstrndup(filecmdstr+start, idx-start+hack+1);
	if (hack)
		(*retval)[idx] = '\\';

	return idx;
}
