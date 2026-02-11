insertline(LogColor color, char *line)
{
	if (count() >= maxlinecount) deletefirstline();
	vcp c;
	switch (color) {
		case LOG_NORMAL: c = VCP(VC_WHITE, VC_TRANSPARENT); break;
		case LOG_WARN: c = VCP(VC_LIGHT(VC_YELLOW), VC_TRANSPARENT); break;
		case LOG_ERROR: c = VCP(VC_LIGHT(VC_RED), VC_TRANSPARENT); break;
		default: c = VCP(VC_WHITE, VC_TRANSPARENT); break;
	}
	insert(new ht_log_msg(c, line));
}
