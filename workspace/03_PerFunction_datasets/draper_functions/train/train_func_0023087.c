ast_fax_log(int level, const char *file, const int line, const char *function, const char *msg)
{
	if (fax_logger_level != -1) {
		ast_log_dynamic_level(fax_logger_level, "%s", msg);
	} else {
		ast_log(level, file, line, function, "%s", msg);
	}
}
