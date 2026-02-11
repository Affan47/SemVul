updatetags(const char *dbpath, const char *root, IDSET *deleteset, STRBUF *addlist, int db)
{
	GTOP *gtop;
	STRBUF *comline = strbuf_open(0);
	int seqno;


	if (db == GRTAGS && !test("f", makepath(dbpath, dbname(GTAGS), NULL)))
		die("GTAGS needed to create GRTAGS.");


	if (!getconfs(dbname(db), comline))
		die("cannot get tag command. (%s)", dbname(db));
	gtop = gtags_open(dbpath, root, db, GTAGS_MODIFY);
	if (vflag) {
		char fid[32];
		const char *path;
		int total = idset_count(deleteset);
		unsigned int id;

		seqno = 1;
		for (id = idset_first(deleteset); id != END_OF_ID; id = idset_next(deleteset)) {
			snprintf(fid, sizeof(fid), "%d", id);
			path = gpath_fid2path(fid, NULL);
			if (path == NULL)
				die("GPATH is corrupted.");
			fprintf(stderr, " [%d/%d] deleting tags of %s\n", seqno++, total, path + 2);
		}
	}
	if (!idset_empty(deleteset))
		gtags_delete(gtop, deleteset);
	gtop->flags = 0;
	if (extractmethod)
		gtop->flags |= GTAGS_EXTRACTMETHOD;
	if (debug)
		gtop->flags |= GTAGS_DEBUG;


	{
		XARGS *xp;
		char *ctags_x;
		char tag[MAXTOKEN], *p;

		xp = xargs_open_with_strbuf(strbuf_value(comline), max_args, addlist);
		xp->put_gpath = 1;
		if (vflag)
			xp->verbose = verbose_updatetags;
		while ((ctags_x = xargs_read(xp)) != NULL) {
			strlimcpy(tag, strmake(ctags_x, " \t"), sizeof(tag));


			p = tag;
			if (gtop->flags & GTAGS_EXTRACTMETHOD) {
				if ((p = locatestring(tag, ".", MATCH_LAST)) != NULL)
					p++;
				else if ((p = locatestring(tag, "::", MATCH_LAST)) != NULL)
					p += 2;
				else
					p = tag;
			}
			gtags_put(gtop, p, ctags_x);
		}
		total = xargs_close(xp);
	}
	gtags_close(gtop);
	strbuf_close(comline);
}
