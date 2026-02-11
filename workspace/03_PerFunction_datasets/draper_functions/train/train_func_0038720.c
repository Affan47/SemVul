lo_import_internal(text *filename, Oid lobjOid)
{
	File		fd;
	int			nbytes,
				tmp;
	char		buf[BUFSIZE];
	char		fnamebuf[MAXPGPATH];
	LargeObjectDesc *lobj;
	Oid			oid;

#ifndef ALLOW_DANGEROUS_LO_FUNCTIONS
	if (!superuser())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("must be superuser to use server-side lo_import()"),
				 errhint("Anyone can use the client-side lo_import() provided by libpq.")));
#endif

	CreateFSContext();


	text_to_cstring_buffer(filename, fnamebuf, sizeof(fnamebuf));
	fd = PathNameOpenFile(fnamebuf, O_RDONLY | PG_BINARY, 0666);
	if (fd < 0)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not open server file \"%s\": %m",
						fnamebuf)));


	oid = inv_create(lobjOid);


	lobj = inv_open(oid, INV_WRITE, fscxt);

	while ((nbytes = FileRead(fd, buf, BUFSIZE)) > 0)
	{
		tmp = inv_write(lobj, buf, nbytes);
		Assert(tmp == nbytes);
	}

	if (nbytes < 0)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not read server file \"%s\": %m",
						fnamebuf)));

	inv_close(lobj);
	FileClose(fd);

	return oid;
}
