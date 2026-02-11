log_char(long level, char c)
{
	int i;

	if ((logdbg & level) || (level == L_FATAL) || (level == L_STDERR)) {
		if (!isprint(c)) {
			i = 0;
			while (logsequence[i].text) {
				if (logsequence[i].code == c) {
					log_text(level, "%s", logsequence[i].text);
					return;
				}
				i++;
			}
			log_text(level, "[0x%02X]", (unsigned char)c);
		} else {
			log_text(level, "%c", c);
		}
	}
}
