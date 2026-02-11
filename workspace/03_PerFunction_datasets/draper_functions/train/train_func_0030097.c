conf_match_num(char *section, char *tag, int x)
{
	char	*value = conf_get_str(section, tag);
	int	 val, min, max, n;

	if (!value)
		return 0;
	n = sscanf(value, "%d,%d:%d", &val, &min, &max);
	switch (n) {
	case 1:
		LOG_DBG((LOG_MISC, 95, "conf_match_num: %s:%s %d==%d?",
		    section, tag, val, x));
		return x == val;
	case 3:
		LOG_DBG((LOG_MISC, 95, "conf_match_num: %s:%s %d<=%d<=%d?",
		    section, tag, min, x, max));
		return min <= x && max >= x;
	default:
		log_error("conf_match_num: section %s tag %s: invalid number "
		    "spec %s", section, tag, value);
	}
	return 0;
}
