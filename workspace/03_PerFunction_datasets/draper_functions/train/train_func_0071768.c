gn_atem_command_diesis(char **buf)
{
	int	number;
	char	buffer[MAX_LINE_LENGTH];

	if (strncasecmp(*buf, "CID", 3) == 0) {
		buf[0] += 3;
		switch (**buf) {
		case '?':
			buf[0]++;
			gsprintf(buffer, MAX_LINE_LENGTH, "%d\r\n", CallerIDMode);
			gn_atem_string_out(buffer);
			return (false);
		case '=':
			buf[0]++;
			if (**buf == '?') {
				buf[0]++;
				gn_atem_string_out("0,1\r\n");
				return (false);
			} else {
				number = gn_atem_num_get(buf);
				if ( number == 0 || number == 1 ) {
					CallerIDMode = number;
					return (false);
				}
			}
		}
	}
	return (true);
}
