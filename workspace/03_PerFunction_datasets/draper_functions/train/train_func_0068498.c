uniqkanji(argc, argv)
long argc;
kanjitable *argv;
{
	long i, j;
	int c;

	for (i = 0L; i < argc - 1; i++) {
		for (j = i + 1L; j < argc; j++) {
			if (argv[i].k.max != argv[j].k.max) break;
			c = memcmp((char *)(argv[i].k.buf),
				(char *)(argv[j].k.buf),
				argv[i].k.max * sizeof(u_short));
			if (c) break;

			Xfree(argv[j].k.buf);
			if (argv[j].len > argv[i].len) {
				argv[i].len = argv[j].len;
				argv[i].freq = argv[j].freq;
			}
			else if (argv[j].len < argv[i].len) continue;
			else if (argv[j].freq > argv[i].freq)
				argv[i].freq = argv[j].freq;
		}
		if (j <= i + 1L) continue;
		memmove((char *)&(argv[i + 1]), (char *)&(argv[j]),
			(argc + 1 - j) * sizeof(kanjitable));
		argc -= --j - i;
	}

	return(argc);
}
