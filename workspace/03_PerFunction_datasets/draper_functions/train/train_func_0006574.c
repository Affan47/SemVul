opengl_check_for_errors(char *err_at)
{
#ifdef NDEBUG
	return 0;
#endif
	const char *error_str = NULL;
	int num_errors = 0;

	error_str = opengl_error_string();

	if (error_str) {
		if (err_at != NULL) {
			nprintf(("OpenGL", "OpenGL Error from %s: %s\n", err_at, error_str));
		} else {
			nprintf(("OpenGL", "OpenGL Error: %s\n", error_str));
		}

		num_errors++;
	}

	return num_errors;
}
