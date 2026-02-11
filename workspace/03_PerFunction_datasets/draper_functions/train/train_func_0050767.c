dumpUndefinedType(Archive *fout, DumpOptions *dopt, TypeInfo *tyinfo)
{
	PQExpBuffer q = createPQExpBuffer();
	PQExpBuffer delq = createPQExpBuffer();
	PQExpBuffer labelq = createPQExpBuffer();
	char	   *qtypname;

	qtypname = pg_strdup(fmtId(tyinfo->dobj.name));


	appendPQExpBuffer(delq, "DROP TYPE %s.",
					  fmtId(tyinfo->dobj.namespace->dobj.name));
	appendPQExpBuffer(delq, "%s;\n",
					  qtypname);

	if (dopt->binary_upgrade)
		binary_upgrade_set_type_oids_by_type_oid(fout,
												 q, tyinfo->dobj.catId.oid);

	appendPQExpBuffer(q, "CREATE TYPE %s;\n",
					  qtypname);

	appendPQExpBuffer(labelq, "TYPE %s", qtypname);

	if (dopt->binary_upgrade)
		binary_upgrade_extension_member(q, &tyinfo->dobj, labelq->data);

	ArchiveEntry(fout, tyinfo->dobj.catId, tyinfo->dobj.dumpId,
				 tyinfo->dobj.name,
				 tyinfo->dobj.namespace->dobj.name,
				 NULL,
				 tyinfo->rolname, false,
				 "TYPE", SECTION_PRE_DATA,
				 q->data, delq->data, NULL,
				 NULL, 0,
				 NULL, NULL);


	dumpComment(fout, dopt, labelq->data,
				tyinfo->dobj.namespace->dobj.name, tyinfo->rolname,
				tyinfo->dobj.catId, 0, tyinfo->dobj.dumpId);
	dumpSecLabel(fout, dopt, labelq->data,
				 tyinfo->dobj.namespace->dobj.name, tyinfo->rolname,
				 tyinfo->dobj.catId, 0, tyinfo->dobj.dumpId);

	dumpACL(fout, dopt, tyinfo->dobj.catId, tyinfo->dobj.dumpId, "TYPE",
			qtypname, NULL, tyinfo->dobj.name,
			tyinfo->dobj.namespace->dobj.name,
			tyinfo->rolname, tyinfo->typacl);

	destroyPQExpBuffer(q);
	destroyPQExpBuffer(delq);
	destroyPQExpBuffer(labelq);
}
