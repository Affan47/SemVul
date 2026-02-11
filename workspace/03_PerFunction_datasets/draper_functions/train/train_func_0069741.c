add_user_info(const char *what, enum cmit_fmt fmt, char *buf,
			 const char *line, enum date_mode dmode,
			 const char *encoding)
{
	char *date;
	int namelen;
	unsigned long time;
	int tz, ret;
	const char *filler = "    ";

	if (fmt == CMIT_FMT_ONELINE)
		return 0;
	date = strchr(line, '>');
	if (!date)
		return 0;
	namelen = ++date - line;
	time = strtoul(date, &date, 10);
	tz = strtol(date, NULL, 10);

	if (fmt == CMIT_FMT_EMAIL) {
		char *name_tail = strchr(line, '<');
		int display_name_length;
		if (!name_tail)
			return 0;
		while (line < name_tail && isspace(name_tail[-1]))
			name_tail--;
		display_name_length = name_tail - line;
		filler = "";
		strcpy(buf, "From: ");
		ret = strlen(buf);
		ret += add_rfc2047(buf + ret, line, display_name_length,
				   encoding);
		memcpy(buf + ret, name_tail, namelen - display_name_length);
		ret += namelen - display_name_length;
		buf[ret++] = '\n';
	}
	else {
		ret = sprintf(buf, "%s: %.*s%.*s\n", what,
			      (fmt == CMIT_FMT_FULLER) ? 4 : 0,
			      filler, namelen, line);
	}
	switch (fmt) {
	case CMIT_FMT_MEDIUM:
		ret += sprintf(buf + ret, "Date:   %s\n",
			       show_date(time, tz, dmode));
		break;
	case CMIT_FMT_EMAIL:
		ret += sprintf(buf + ret, "Date: %s\n",
			       show_rfc2822_date(time, tz));
		break;
	case CMIT_FMT_FULLER:
		ret += sprintf(buf + ret, "%sDate: %s\n", what,
			       show_date(time, tz, dmode));
		break;
	default:

		break;
	}
	return ret;
}
