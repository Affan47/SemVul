EditAbbrevs()
{
	char	tname[128];
	static const char	EditName[] = "Abbreviation Edit";
	Buffer	*obuf = curbuf,
		*ebuf;

	if ((ebuf = buf_exists(EditName)) != NULL) {
		if (ebuf->b_type != B_SCRATCH)
			confirm("Over-write buffer %b? ", ebuf);
	}
	SetBuf(ebuf = do_select(curwind, EditName));
	ebuf->b_type = B_SCRATCH;
	buf_clear(ebuf);


	PathCat(tname, sizeof(tname), TmpDir,
#ifdef MAC
		".jabbXXX"
#else
		"jabbXXXXXX"
#endif
		);


	close(MakeTemp(tname, "cannot create tempfile \"%s\""));

	save_abbrevs(tname);
	setfname(ebuf, tname);
	read_file(tname, NO);
	message("[Edit definitions and then type ^X ^C]");
	Recur();
	if (IsModified(ebuf)) {
		file_write(tname, NO);
		rest_abbrevs(tname);
	}
	(void) unlink(tname);
	if (valid_bp(obuf))
		SetBuf(do_select(curwind, obuf->b_name));
}
