check_emacsclient_version(void)
{
	struct strbuf buffer = STRBUF_INIT;
	struct child_process ec_process;
	const char *argv_ec[] = { "emacsclient", "--version", NULL };
	int version;


	memset(&ec_process, 0, sizeof(ec_process));
	ec_process.argv = argv_ec;
	ec_process.err = -1;
	ec_process.stdout_to_stderr = 1;
	if (start_command(&ec_process))
		return error("Failed to start emacsclient.");

	strbuf_read(&buffer, ec_process.err, 20);
	close(ec_process.err);


	finish_command(&ec_process);

	if (prefixcmp(buffer.buf, "emacsclient")) {
		strbuf_release(&buffer);
		return error("Failed to parse emacsclient version.");
	}

	strbuf_remove(&buffer, 0, strlen("emacsclient"));
	version = atoi(buffer.buf);

	if (version < 22) {
		strbuf_release(&buffer);
		return error("emacsclient version '%d' too old (< 22).",
			version);
	}

	strbuf_release(&buffer);
	return 0;
}
