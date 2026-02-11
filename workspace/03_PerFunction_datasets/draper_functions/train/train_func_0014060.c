tyan_lcdm_read_key(int fd)
{
	int count = 0;
	char key_str[4];

	memset(key_str, '\0', 4);
	count = read(fd, key_str, 4);
	if ((count == 4)
	    && (key_str[0] == (char) TYAN_LCDM_CMD_BEGIN)
	    && (key_str[1] == (char) 0x72)
	    && (key_str[3] == (char) TYAN_LCDM_CMD_END)) {
		return key_str[2];
	}
	return 0xF4;
}
