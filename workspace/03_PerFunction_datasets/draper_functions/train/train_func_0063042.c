clar__assert(
	int condition,
	const char *file,
	int line,
	const char *error_msg,
	const char *description,
	int should_abort)
{
	if (condition)
		return;

	clar__fail(file, line, error_msg, description, should_abort);
}
