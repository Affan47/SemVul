parse_timezone_offset(const char *buffer, int *offset_out)
{
	int dec_offset;
	int mins, hours, offset;

	const char *offset_start;
	const char *offset_end;

	offset_start = buffer;

	if (*offset_start == '\n') {
		*offset_out = 0;
		return 0;
	}

	if (offset_start[0] != '-' && offset_start[0] != '+')
		return timezone_error("does not start with '+' or '-'");

	if (offset_start[1] < '0' || offset_start[1] > '9')
		return timezone_error("expected initial digit");

	if (git__strtol32(&dec_offset, offset_start + 1, &offset_end, 10) < 0)
		return timezone_error("not a valid number");

	if (offset_end - offset_start != 5)
		return timezone_error("invalid length");

	if (dec_offset > 1400)
		return timezone_error("value too large");

	hours = dec_offset / 100;
	mins = dec_offset % 100;

	if (hours > 14)
		return timezone_error("hour value too large");

	if (mins > 59)
		return timezone_error("minutes value too large");

	offset = (hours * 60) + mins;

	if (offset_start[0] == '-')
		offset *= -1;

	*offset_out = offset;

	return 0;
}
