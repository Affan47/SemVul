error_string(int error)
{
    const char *str;
    const char *error_str;
    static const char unknown_error[] = "Unknown error";

    error_str = unknown_error;

    if (error > 0) {
	char *str = strerror(error);
	if (str)
	    error_str = str;
    }
    else if (error < 0) {
	str = emtp_error_string(error);
	if (!str) {
	    str = emtbt_error_string(error);
	    if (!str) {
		switch (error) {
		case EM_TRUNCATED_TRACE_ERROR:
		    error_str = "Truncated trace";
		    break;
		case EM_INTERNAL_ERROR:
		    error_str = "emem internal error";
		    break;
		default:
		    break;
		}
	    }
	}

	if (str)
	    error_str = str;
    }

    return error_str;
}
