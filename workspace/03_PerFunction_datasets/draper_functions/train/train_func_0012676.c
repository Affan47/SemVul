git_signature__parse(git_signature *sig, const char **buffer_out,
		const char *buffer_end, const char *header)
{
	const size_t header_len = strlen(header);

	int name_length, email_length;
	const char *buffer = *buffer_out;
	const char *line_end, *name_end, *email_end;
	long offset = 0, time;

	memset(sig, 0x0, sizeof(git_signature));

	line_end = memchr(buffer, '\n', buffer_end - buffer);
	if (!line_end)
		return git__throw(GIT_EOBJCORRUPTED, "Failed to parse signature. No newline found");;

	if (buffer + (header_len + 1) > line_end)
		return git__throw(GIT_EOBJCORRUPTED, "Failed to parse signature. Signature too short");

	if (memcmp(buffer, header, header_len) != 0)
		return git__throw(GIT_EOBJCORRUPTED, "Failed to parse signature. Expected prefix '%s' doesn't match actual", header);

	buffer += header_len;


	if ((name_end = memchr(buffer, '<', buffer_end - buffer)) == NULL)
		return git__throw(GIT_EOBJCORRUPTED, "Failed to parse signature. Can't find e-mail start");

	name_length = name_end - buffer - 1;
	sig->name = git__malloc(name_length + 1);
	if (sig->name == NULL)
		return GIT_ENOMEM;

	memcpy(sig->name, buffer, name_length);
	sig->name[name_length] = 0;
	buffer = name_end + 1;

	if (buffer >= line_end)
		return git__throw(GIT_EOBJCORRUPTED, "Failed to parse signature. Ended unexpectedly");


	if ((email_end = memchr(buffer, '>', buffer_end - buffer)) == NULL)
		return git__throw(GIT_EOBJCORRUPTED, "Failed to parse signature. Can't find e-mail end");

	email_length = email_end - buffer;
	sig->email = git__malloc(email_length + 1);
	if (sig->name == NULL)
		return GIT_ENOMEM;

	memcpy(sig->email, buffer, email_length);
	sig->email[email_length] = 0;
	buffer = email_end + 1;

	if (buffer >= line_end)
		return git__throw(GIT_EOBJCORRUPTED, "Failed to parse signature. Ended unexpectedly");

	if (git__strtol32(&time, buffer, &buffer, 10) < GIT_SUCCESS)
		return git__throw(GIT_EOBJCORRUPTED, "Failed to parse signature. Timestamp isn't a number");

	sig->when.time = (time_t)time;

	if (parse_timezone_offset(buffer, &offset) < GIT_SUCCESS)
		return GIT_EOBJCORRUPTED;

	sig->when.offset = offset;

	*buffer_out = (line_end + 1);
	return GIT_SUCCESS;
}
