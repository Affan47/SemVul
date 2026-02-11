vdebugf(size_t level, const char *format, va_list args)
{
	if (debug_level_match(level))
	{
		char mesg[MSG_SIZE], prefix[32] = "";
		vsnprintf(mesg, MSG_SIZE, format, args);

		if (level & 0xffffff00)
			snprintf(prefix, 32, " [%d]", (int)((level & 0xffffff00) >> 8));

		if (prog_name())
			msg_out(prog_dbg(), "%s: debug:%s%*s%s\n", prog_name(), prefix, level & 0xff, "", mesg);
		else
			msg_out(prog_dbg(), "debug:%s%*s%s\n", prefix, level & 0xff, "", mesg);
	}
}
