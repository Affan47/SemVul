parse_output_signals(const char *value, int *line)
{


	*line = 0;

	if (strstr(value, "DTR") && !strstr(value, "-DTR")) {
		*line |= TIOCM_DTR;
	}

	if (strstr(value, "RTS") && !strstr(value, "-RTS")) {
		*line |= TIOCM_RTS;
	}

	if (strstr(value, "ST")) {
		*line |= TIOCM_ST;
	}

	if (strstr(value, "CTS")) {
		fatalx(EXIT_FAILURE, "Can't override output with CTS (not an output)");
	}

	if (strstr(value, "DCD")) {
		fatalx(EXIT_FAILURE, "Can't override output with DCD (not an output)");
	}

	if (strstr(value, "RNG")) {
		fatalx(EXIT_FAILURE, "Can't override output with RNG (not an output)");
	}

	if (strstr(value, "DSR")) {
		fatalx(EXIT_FAILURE, "Can't override output with DSR (not an output)");
	}
}
