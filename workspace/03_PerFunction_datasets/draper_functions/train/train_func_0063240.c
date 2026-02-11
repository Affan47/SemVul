dumpNamespace(Archive *fout, NamespaceInfo *nspinfo)
{
	PQExpBuffer q;
	PQExpBuffer delq;
	PQExpBuffer labelq;
	char	   *qnspname;


	if (!nspinfo->dobj.dump || dataOnly)
		return;


	if (strlen(nspinfo->dobj.name) == 0)
		return;

	q = createPQExpBuffer();
	delq = createPQExpBuffer();
	labelq = createPQExpBuffer();

	qnspname = strdup(fmtId(nspinfo->dobj.name));

	appendPQExpBuffer(delq, "DROP SCHEMA %s;\n", qnspname);

	appendPQExpBuffer(q, "CREATE SCHEMA %s;\n", qnspname);

	appendPQExpBuffer(labelq, "SCHEMA %s", qnspname);

	if (binary_upgrade)
		binary_upgrade_extension_member(q, &nspinfo->dobj, labelq->data);

	ArchiveEntry(fout, nspinfo->dobj.catId, nspinfo->dobj.dumpId,
				 nspinfo->dobj.name,
				 NULL, NULL,
				 nspinfo->rolname,
				 false, "SCHEMA", SECTION_PRE_DATA,
				 q->data, delq->data, NULL,
				 nspinfo->dobj.dependencies, nspinfo->dobj.nDeps,
				 NULL, NULL);


	dumpComment(fout, labelq->data,
				NULL, nspinfo->rolname,
				nspinfo->dobj.catId, 0, nspinfo->dobj.dumpId);
	dumpSecLabel(fout, labelq->data,
				 NULL, nspinfo->rolname,
				 nspinfo->dobj.catId, 0, nspinfo->dobj.dumpId);

	dumpACL(fout, nspinfo->dobj.catId, nspinfo->dobj.dumpId, "SCHEMA",
			qnspname, NULL, nspinfo->dobj.name, NULL,
			nspinfo->rolname, nspinfo->nspacl);

	free(qnspname);

	destroyPQExpBuffer(q);
	destroyPQExpBuffer(delq);
	destroyPQExpBuffer(labelq);
}
