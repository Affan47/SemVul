fdlock(f)

struct fdesc		*f;

{
	int		nlock;
	struct fdesc	*p;

	if (f->f_tflags & FLOCK) {
		return(0);
	}

	fdactivate(f);
	nlock = 0;

	for (p = fdtop; p != FDNULL; p = p->f_next) {

		if (p->f_tflags & FLOCK) {
			++nlock;
		}
	}

	if (nlock >= (ACTIVEMAX - 1)) {
		errno = ENFILE;
		return(ERROR);
	}

	f->f_tflags |= FLOCK;
	return(0);
}
