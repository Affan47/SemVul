copyContents()
{
	off_t start_pos, end_pos, start_body;

	off_t nlines, nbodylines;

	rfc2045_mimepos(rfcp, &start_pos, &end_pos, &start_body,
			&nlines, &nbodylines);

	if (lseek(fd, start_pos, SEEK_SET) < 0)
		return false;

	end_pos -= start_pos;

	return copy(fd, &end_pos, account, readType, callback);
}
