show_shost_mode(unsigned int mode, char *buf)
{
	ssize_t len = 0;

	if (mode & MODE_INITIATOR)
		len = sprintf(buf, "%s", "Initiator");

	if (mode & MODE_TARGET)
		len += sprintf(buf + len, "%s%s", len ? ", " : "", "Target");

	len += sprintf(buf + len, "\n");

	return len;
}
