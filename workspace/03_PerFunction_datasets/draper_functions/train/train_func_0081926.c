freekanjilist(argv)
u_short **argv;
{
	long n, argc;

	if (argv) {
		for (argc = 0L; argv[argc]; argc++) {
			if (kanjilist) {
				for (n = 0L; kanjilist[n].k.buf; n++)
					if (argv[argc] == kanjilist[n].k.buf)
						break;
				if (kanjilist[n].k.buf) continue;
			}
			Xfree(argv[argc]);
		}
		Xfree(argv);
	}
	freekanji(kanjilist);
	kanjilist = NULL;
}
