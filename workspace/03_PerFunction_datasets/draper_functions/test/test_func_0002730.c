line_ending(struct crlf_filter *filter)
{
	switch (filter->attrs.crlf_action) {
	case GIT_CRLF_BINARY:
	case GIT_CRLF_INPUT:
		return "\n";

	case GIT_CRLF_CRLF:
		return "\r\n";

	case GIT_CRLF_AUTO:
	case GIT_CRLF_TEXT:
	case GIT_CRLF_GUESS:
		break;

	default:
		goto line_ending_error;
	}

	switch (filter->attrs.eol) {
	case GIT_EOL_UNSET:
		return GIT_EOL_NATIVE == GIT_EOL_CRLF
			? "\r\n"
			: "\n";

	case GIT_EOL_CRLF:
		return "\r\n";

	case GIT_EOL_LF:
		return "\n";

	default:
		goto line_ending_error;
	}

line_ending_error:
	giterr_set(GITERR_INVALID, "Invalid input to line ending filter");
	return NULL;
}
