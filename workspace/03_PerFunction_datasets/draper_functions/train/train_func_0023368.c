build_log_entry(const char *format, GttProject *proj)
{
	if (!format || !format[0])
		format = config_logfile_start;
	if (!proj)
		return g_strdup(_("program started"));

	return printf_project (format, proj);
}
