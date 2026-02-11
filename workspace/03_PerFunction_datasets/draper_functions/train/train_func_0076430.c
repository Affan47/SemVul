dowrite(const ssize_t rd)
{
	int errs = 0;
	int fatal = 0;

	ssize_t wr = 0;
	if (!sparse || blockiszero(buf, rd) < rd)
		errs += ((wr = writeblock(rd)) < rd ? 1: 0);
	advancepos(rd, wr);
	if (wr <= 0 && (errno == ENOSPC
		   || (errno == EFBIG && !reverse)))
		++fatal;
	if (rd != wr && !sparse) {
		fplog(stderr, "dd_rescue: (warning): assumption rd(%i) == wr(%i) failed! \n", rd, wr);
		fplog(stderr, "dd_rescue: (%s): write %s (%.1fk): %s!\n",
		      (fatal? "fatal": "warning"), oname,
		      (float)opos/1024, strerror(errno));
		fprintf(stderr, "%s%s%s", down, down, down);
		errno = 0;
	}
	return fatal? -errs: errs;
}
