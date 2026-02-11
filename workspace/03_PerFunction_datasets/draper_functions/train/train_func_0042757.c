createCrashLogFile(char *filename, time_t t) {
	char *end = filename;
	end = appendText(end, "/var/tmp/passenger-crash-log.");
	end = appendULL(end, (unsigned long long) t);
	*end = '\0';

	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1) {
		end = filename;
		end = appendText(end, "/tmp/passenger-crash-log.");
		end = appendULL(end, (unsigned long long) t);
		*end = '\0';
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	}
	if (fd == -1) {
		*filename = '\0';
		return false;
	} else {
		close(fd);
		return true;
	}
}
