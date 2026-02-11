get_tracef_max(void)
{
	static Boolean calculated = False;
	char *ptr;
	Boolean bad = False;

	if (calculated)
		return;

	calculated = True;

	if (appres.trace_file_size == CN ||
	    !strcmp(appres.trace_file_size, "0") ||
	    !strncasecmp(appres.trace_file_size, "none",
			 strlen(appres.trace_file_size))) {
		tracef_max = 0;
		return;
	}

	tracef_max = strtoul(appres.trace_file_size, &ptr, 0);
	if (tracef_max == 0 || ptr == appres.trace_file_size || *(ptr + 1)) {
		bad = True;
	} else switch (*ptr) {
	case 'k':
	case 'K':
		tracef_max *= 1024;
		break;
	case 'm':
	case 'M':
		tracef_max *= 1024 * 1024;
		break;
	case '\0':
		break;
	default:
		bad = True;
		break;
	}

	if (bad) {
		tracef_max = MIN_TRACEFILE_SIZE;
#if defined(X3270_DISPLAY)
		popup_an_info("Invalid %s '%s', assuming "
		    MIN_TRACEFILE_SIZE_NAME,
		    ResTraceFileSize,
		    appres.trace_file_size);
#endif
	} else if (tracef_max < MIN_TRACEFILE_SIZE) {
		tracef_max = MIN_TRACEFILE_SIZE;
	}
}
