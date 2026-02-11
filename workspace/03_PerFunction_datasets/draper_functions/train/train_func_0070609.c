_searchdict(argc, argvp, kp, fd)
long argc;
kanjitable **argvp, *kp;
int fd;
{
	kanjitable *argv2, tmp;
	off_t curofs;
	long argc2;
	u_char c;
	int n;

	dictofs = (off_t)0;
	tmp.k.buf = kp -> k.buf;
	tmp.k.max = kp -> len;
	if (finddict(&(tmp.k), fd, &(kp -> ofs)) <= 0) return(argc);

	if (fgetbyte(&c, fd) < 0) return(argc);
	if (c <= 1) return(addkanjilist(argc, argvp, 0, NULL, kp, fd));

	curofs = dictlseek(fd, (off_t)0, L_INCR);
	if (curofs < (off_t)0) return(argc);
	argv2 = NULL;
	argc2 = 0L;
	if (hinsitblent > 0 && kp -> len < kp -> k.max) {
		tmp.k.buf = &(kp -> k.buf[kp -> len]);
		tmp.k.max = kp -> k.max - kp -> len;
		tmp.hinsi[0] = MAXUTYPE(u_short);
		for (tmp.len = kp -> k.max; tmp.len > (u_char)0; tmp.len--)
			argc2 = _searchdict(argc2, &argv2, &tmp, fd);
		if (!argv2) return(argc);
	}

	if (dictlseek(fd, curofs, L_SET) >= (off_t)0) {
		for (n = 0; n < c; n++, curofs = nextofs(curofs, fd)) {
			if (curofs < (off_t)0) break;
			argc = addkanjilist(argc, argvp, argc2, argv2, kp, fd);
		}
	}

	freekanji(argv2);

	return(argc);
}
