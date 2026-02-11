dumpFileDescriptorInfo(AbortHandlerState &state) {
	char *messageBuf = state.messageBuf;
	char *end;
	struct stat buf;
	int status;

	end = messageBuf;
	end = appendText(end, state.messagePrefix);
	end = appendText(end, " ] Open files and file descriptors:\n");
	write_nowarn(STDERR_FILENO, messageBuf, end - messageBuf);

	status = runInSubprocessWithTimeLimit(state, dumpFileDescriptorInfoWithLsof, NULL, 4000);

	if (status != 0) {
		safePrintErr("Falling back to another mechanism for dumping file descriptors.\n");

		end = messageBuf;
		end = appendText(end, "/proc/");
		end = appendULL(end, state.pid);
		end = appendText(end, "/fd");
		*end = '\0';
		if (stat(messageBuf, &buf) == 0) {
			dumpFileDescriptorInfoWithLs(state, end + 1);
		} else {
			end = messageBuf;
			end = appendText(end, "/dev/fd");
			*end = '\0';
			if (stat(messageBuf, &buf) == 0) {
				dumpFileDescriptorInfoWithLs(state, end + 1);
			} else {
				end = messageBuf;
				end = appendText(end, "ERROR: No other file descriptor dumping mechanism on current platform detected.\n");
				write_nowarn(STDERR_FILENO, messageBuf, end - messageBuf);
			}
		}
	}
}
