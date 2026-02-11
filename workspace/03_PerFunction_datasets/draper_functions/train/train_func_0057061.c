git_signature__parse(git_signature *sig, const char **buffer_out,
		const char *buffer_end, const char *header, char ender)
{
	const char *buffer = *buffer_out;
	const char *email_start, *email_end;

	memset(sig, 0, sizeof(git_signature));

	if ((buffer_end = memchr(buffer, ender, buffer_end - buffer)) == NULL)
		return signature_error("no newline given");

	if (header) {
		const size_t header_len = strlen(header);

		if (buffer + header_len >= buffer_end || memcmp(buffer, header, header_len) != 0)
			return signature_error("expected prefix doesn't match actual");

		buffer += header_len;
	}

	email_start = git__memrchr(buffer, '<', buffer_end - buffer);
	email_end = git__memrchr(buffer, '>', buffer_end - buffer);

	if (!email_start || !email_end || email_end <= email_start)
		return signature_error("malformed e-mail");

	email_start += 1;
	sig->name = extract_trimmed(buffer, email_start - buffer - 1);
	sig->email = extract_trimmed(email_start, email_end - email_start);


	if (email_end + 2 < buffer_end) {
		const char *time_start = email_end + 2;
		const char *time_end;

		if (git__strtol64(&sig->when.time, time_start, &time_end, 10) < 0)
			return signature_error("invalid Unix timestamp");


		if (time_end + 1 < buffer_end) {
			int offset, hours, mins;
			const char *tz_start, *tz_end;

			tz_start = time_end + 1;

			if ((tz_start[0] != '-' && tz_start[0] != '+') ||
				git__strtol32(&offset, tz_start + 1, &tz_end, 10) < 0) {

				offset = 0;
			}

			hours = offset / 100;
			mins = offset % 100;


			if (hours < 14 && mins < 59) {
				sig->when.offset = (hours * 60) + mins;
				if (tz_start[0] == '-')
					sig->when.offset = -sig->when.offset;
			}
		}
	}

	*buffer_out = buffer_end + 1;
	return 0;
}
