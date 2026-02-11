unpack(void)
{
	struct pack_header hdr;
	const char *hdr_err;
	char hdr_arg[38];

	hdr_err = parse_pack_header(&hdr);
	if (hdr_err)
		return hdr_err;
	snprintf(hdr_arg, sizeof(hdr_arg),
			"--pack_header=%"PRIu32",%"PRIu32,
			ntohl(hdr.hdr_version), ntohl(hdr.hdr_entries));

	if (ntohl(hdr.hdr_entries) < unpack_limit) {
		int code, i = 0;
		const char *unpacker[4];
		unpacker[i++] = "unpack-objects";
		if (receive_fsck_objects)
			unpacker[i++] = "--strict";
		unpacker[i++] = hdr_arg;
		unpacker[i++] = NULL;
		code = run_command_v_opt(unpacker, RUN_GIT_CMD);
		switch (code) {
		case 0:
			return NULL;
		case -ERR_RUN_COMMAND_FORK:
			return "unpack fork failed";
		case -ERR_RUN_COMMAND_EXEC:
			return "unpack execute failed";
		case -ERR_RUN_COMMAND_WAITPID:
			return "waitpid failed";
		case -ERR_RUN_COMMAND_WAITPID_WRONG_PID:
			return "waitpid is confused";
		case -ERR_RUN_COMMAND_WAITPID_SIGNAL:
			return "unpacker died of signal";
		case -ERR_RUN_COMMAND_WAITPID_NOEXIT:
			return "unpacker died strangely";
		default:
			return "unpacker exited with error code";
		}
	} else {
		const char *keeper[7];
		int s, status, i = 0;
		char keep_arg[256];
		struct child_process ip;

		s = sprintf(keep_arg, "--keep=receive-pack %i on ", getpid());
		if (gethostname(keep_arg + s, sizeof(keep_arg) - s))
			strcpy(keep_arg + s, "localhost");

		keeper[i++] = "index-pack";
		keeper[i++] = "--stdin";
		if (receive_fsck_objects)
			keeper[i++] = "--strict";
		keeper[i++] = "--fix-thin";
		keeper[i++] = hdr_arg;
		keeper[i++] = keep_arg;
		keeper[i++] = NULL;
		memset(&ip, 0, sizeof(ip));
		ip.argv = keeper;
		ip.out = -1;
		ip.git_cmd = 1;
		if (start_command(&ip))
			return "index-pack fork failed";
		pack_lockfile = index_pack_lockfile(ip.out);
		close(ip.out);
		status = finish_command(&ip);
		if (!status) {
			reprepare_packed_git();
			return NULL;
		}
		return "index-pack abnormal exit";
	}
}
