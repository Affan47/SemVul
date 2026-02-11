log_timestamp(char *s, size_t max)
{
	if (!log)
		return _make_timestamp(s, max, "%Y-%m-%dT%T");
	switch (log->fmt) {
	case LOG_FMT_RFC5424_MS:
	case LOG_FMT_RFC5424:
	{
		size_t written = _make_timestamp(s, max, "%Y-%m-%dT%T%z");
		if (max >= 26 && written == 24) {


			s[25] = '\0';
			s[24] = s[23];
			s[23] = s[22];
			s[22] = ':';
			return written + 1;
		}
		return written;
	}
	case LOG_FMT_SHORT:
		return _make_timestamp(s, max, "%b %d %T");
		break;
	default:
		return _make_timestamp(s, max, "%Y-%m-%dT%T");
		break;
	}
}
