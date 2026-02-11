validate_trace(char *parser_path, char *trace_path)
{
	int ret = 0;
	char babeltrace_output_path[] = "/tmp/babeltrace_output_XXXXXX";
	int babeltrace_output_fd = -1;

	if (!trace_path) {
		ret = -1;
		goto result;
	}

	babeltrace_output_fd = mkstemp(babeltrace_output_path);
	unlink(babeltrace_output_path);

	if (babeltrace_output_fd == -1) {
		diag("Failed to create a temporary file for trace parsing.");
		ret = -1;
		goto result;
	}

	pid_t pid = fork();
	if (pid) {
		int status = 0;
		waitpid(pid, &status, 0);
		ret = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
	} else {
		ret = dup2(babeltrace_output_fd, STDOUT_FILENO);
		if (ret < 0) {
			perror("# dup2 babeltrace_output_fd to STDOUT");
			goto result;
		}

		ret = dup2(babeltrace_output_fd, STDERR_FILENO);
		if (ret < 0) {
			perror("# dup2 babeltrace_output_fd to STDERR");
			goto result;
		}

		execl(parser_path, "babeltrace", trace_path, NULL);
		perror("# Could not launch the babeltrace process");
		exit(-1);
	}
result:
	ok(ret == 0, "Babeltrace could read the resulting trace");

	if (ret && babeltrace_output_fd >= 0) {
		char *line;
		size_t len = METADATA_LINE_SIZE;
		FILE *babeltrace_output_fp = NULL;

		babeltrace_output_fp = fdopen(babeltrace_output_fd, "r");
		if (!babeltrace_output_fp) {
			perror("fdopen on babeltrace_output_fd");
			goto close_fp;
		}
		babeltrace_output_fd = -1;

		line = malloc(len);
		if (!line) {
			diag("malloc error");
		}
		rewind(babeltrace_output_fp);
		while (getline(&line, &len, babeltrace_output_fp) > 0) {
			diag("%s", line);
		}

		free(line);
close_fp:
		if (babeltrace_output_fp) {
			if (fclose(babeltrace_output_fp)) {
				diag("fclose error");
			}
		}
	}

	if (babeltrace_output_fd >= 0) {
		if (close(babeltrace_output_fd)) {
			diag("close error");
		}
	}
}
