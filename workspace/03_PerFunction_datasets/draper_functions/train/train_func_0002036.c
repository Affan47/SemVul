wrap_parse_add_file_msg (char *buf, struct wrap_msg_buf *wmsg)
{
	struct wrap_add_file *	res = &wmsg->body.add_file;
	char *			scan = buf+3;
	char *			p;
	int			rc;

	wmsg->msg_type = WRAP_MSGTYPE_ADD_FILE;

	res->fstat.valid = 0;
	res->fhinfo = WRAP_INVALID_FHINFO;

	while (*scan && *scan == ' ')
		scan++;
	if (*scan == 0)
		return -1;

	p = scan;
	while (*scan && *scan != ' ')
		scan++;

	if (*scan) {
		*scan = 0;
		rc = wrap_cstr_to_str (p, res->path, sizeof res->path);
		*scan++ = ' ';
	} else {
		rc = wrap_cstr_to_str (p, res->path, sizeof res->path);
	}
	if (rc < 0) return -2;

	while (*scan) {
		p = scan+1;
		switch (*scan) {
		case ' ':
			scan++;
			continue;

		case '@':
			res->fhinfo = NDMOS_API_STRTOLL (p, &scan, 0);
			break;

		default:
			rc = wrap_parse_fstat_subr(&scan, &res->fstat);
			if (rc < 0)
				return rc;
			break;
		}

		if (*scan != ' ' && *scan != 0) {

			return -1;
		}
	}

	return 0;
}
