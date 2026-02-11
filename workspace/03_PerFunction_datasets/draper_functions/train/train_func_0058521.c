dumpForeignDataWrapper(Archive *fout, DumpOptions *dopt, FdwInfo *fdwinfo)
{
	PQExpBuffer q;
	PQExpBuffer delq;
	PQExpBuffer labelq;
	char	   *qfdwname;


	if (!fdwinfo->dobj.dump || dopt->dataOnly)
		return;


	if (!fdwinfo->dobj.ext_member)
		if (!dopt->include_everything)
			return;

	q = createPQExpBuffer();
	delq = createPQExpBuffer();
	labelq = createPQExpBuffer();

	qfdwname = pg_strdup(fmtId(fdwinfo->dobj.name));

	appendPQExpBuffer(q, "CREATE FOREIGN DATA WRAPPER %s",
					  qfdwname);

	if (strcmp(fdwinfo->fdwhandler, "-") != 0)
		appendPQExpBuffer(q, " HANDLER %s", fdwinfo->fdwhandler);

	if (strcmp(fdwinfo->fdwvalidator, "-") != 0)
		appendPQExpBuffer(q, " VALIDATOR %s", fdwinfo->fdwvalidator);

	if (strlen(fdwinfo->fdwoptions) > 0)
		appendPQExpBuffer(q, " OPTIONS (\n    %s\n)", fdwinfo->fdwoptions);

	appendPQExpBufferStr(q, ";\n");

	appendPQExpBuffer(delq, "DROP FOREIGN DATA WRAPPER %s;\n",
					  qfdwname);

	appendPQExpBuffer(labelq, "FOREIGN DATA WRAPPER %s",
					  qfdwname);

	if (dopt->binary_upgrade)
		binary_upgrade_extension_member(q, &fdwinfo->dobj, labelq->data);

	ArchiveEntry(fout, fdwinfo->dobj.catId, fdwinfo->dobj.dumpId,
				 fdwinfo->dobj.name,
				 NULL,
				 NULL,
				 fdwinfo->rolname,
				 false, "FOREIGN DATA WRAPPER", SECTION_PRE_DATA,
				 q->data, delq->data, NULL,
				 NULL, 0,
				 NULL, NULL);


	dumpACL(fout, dopt, fdwinfo->dobj.catId, fdwinfo->dobj.dumpId,
			"FOREIGN DATA WRAPPER",
			qfdwname, NULL, fdwinfo->dobj.name,
			NULL, fdwinfo->rolname,
			fdwinfo->fdwacl);


	dumpComment(fout, dopt, labelq->data,
				NULL, fdwinfo->rolname,
				fdwinfo->dobj.catId, 0, fdwinfo->dobj.dumpId);

	free(qfdwname);

	destroyPQExpBuffer(q);
	destroyPQExpBuffer(delq);
	destroyPQExpBuffer(labelq);
}
