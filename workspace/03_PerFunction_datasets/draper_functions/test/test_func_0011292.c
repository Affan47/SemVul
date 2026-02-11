copyfile_softbs(const off_t max)
{
	ssize_t toread;
	int errs = 0; errno = 0;
#if 0
	fprintf(stderr, "%s%s%s%s copyfile (ipos=%.1fk, xfer=%.1fk, max=%.1fk, bs=%i)                         ##\n%s%s%s%s",
		up, up, up, up,
		(float)ipos/1024, (float)xfer/1024, (float)max/1024, softbs,
		down, down, down, down);
#endif


	if (!o_chr)
		pwrite(odes, buf, 0, opos);
	while ((toread = blockxfer(max, softbs)) > 0) {
		int err;
		ssize_t rd = readblock(toread);


		if (rd == 0 && !errno) {
			if (!errs)
				fplog(stderr, "dd_rescue: (info): read %s (%.1fk): EOF\n",
				      iname, (float)ipos/1024);
			return errs;
		}

		if (rd < toread) {
			int ret;
			++errs;

			printstatus(stderr, logfd, softbs, 1);

			exitfatalerr();

			off_t new_max = xfer + toread;

			if (verbose)
				fprintf(stderr, "dd_rescue: (info): problems at ipos %.1fk: %s \n                 fall back to smaller blocksize \n%s%s%s%s",
				        (float)ipos/1024, strerror(errno), down, down, down, down);

			if ((ret = partialwrite(rd)) < 0)
				return ret;
			else
				errs += ret;
			off_t old_xfer = xfer;
			errs += (err = copyfile_hardbs(new_max));

			if (!err && old_xfer == xfer)
				return errs;


			new_max = xfer;
			while (err && (!max || (max-xfer > 0)) && ((!reverse) || (ipos > 0 && opos > 0))) {
				new_max += 2*softbs; old_xfer = xfer;
				if (max && new_max > max)
					new_max = max;
				errs += (err = copyfile_hardbs(new_max));
			}
			errno = 0;

			if (!err && xfer == old_xfer)
				return errs;
			if (verbose)
				fprintf(stderr, "dd_rescue: (info): ipos %.1fk promote to large bs again! \n%s%s%s%s",
					(float)ipos/1024, down, down, down, down);
		} else {
	      		int err = dowrite(rd);
			if (err < 0)
				return -err;
			else
				errs += err;
		}

		if (syncfreq && !(xfer % (syncfreq*softbs)))
			printstatus((quiet? 0: stderr), 0, softbs, 1);
		else if (!quiet && !(xfer % (16*softbs)))
			printstatus(stderr, 0, softbs, 0);
	}
	return errs;
}
