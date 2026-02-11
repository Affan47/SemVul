dumpIndex(Archive *fout, DumpOptions *dopt, IndxInfo *indxinfo)
{
	TableInfo  *tbinfo = indxinfo->indextable;
	bool		is_constraint = (indxinfo->indexconstraint != 0);
	PQExpBuffer q;
	PQExpBuffer delq;
	PQExpBuffer labelq;

	if (dopt->dataOnly)
		return;

	q = createPQExpBuffer();
	delq = createPQExpBuffer();
	labelq = createPQExpBuffer();

	appendPQExpBuffer(labelq, "INDEX %s",
					  fmtId(indxinfo->dobj.name));


	if (!is_constraint)
	{
		if (dopt->binary_upgrade)
			binary_upgrade_set_pg_class_oids(fout, q,
											 indxinfo->dobj.catId.oid, true);


		appendPQExpBuffer(q, "%s;\n", indxinfo->indexdef);


		if (indxinfo->indisclustered)
		{
			appendPQExpBuffer(q, "\nALTER TABLE %s CLUSTER",
							  fmtId(tbinfo->dobj.name));
			appendPQExpBuffer(q, " ON %s;\n",
							  fmtId(indxinfo->dobj.name));
		}


		if (indxinfo->indisreplident)
		{
			appendPQExpBuffer(q, "\nALTER TABLE ONLY %s REPLICA IDENTITY USING",
							  fmtId(tbinfo->dobj.name));
			appendPQExpBuffer(q, " INDEX %s;\n",
							  fmtId(indxinfo->dobj.name));
		}


		appendPQExpBuffer(delq, "DROP INDEX %s.",
						  fmtId(tbinfo->dobj.namespace->dobj.name));
		appendPQExpBuffer(delq, "%s;\n",
						  fmtId(indxinfo->dobj.name));

		ArchiveEntry(fout, indxinfo->dobj.catId, indxinfo->dobj.dumpId,
					 indxinfo->dobj.name,
					 tbinfo->dobj.namespace->dobj.name,
					 indxinfo->tablespace,
					 tbinfo->rolname, false,
					 "INDEX", SECTION_POST_DATA,
					 q->data, delq->data, NULL,
					 NULL, 0,
					 NULL, NULL);
	}


	dumpComment(fout, dopt, labelq->data,
				tbinfo->dobj.namespace->dobj.name,
				tbinfo->rolname,
				indxinfo->dobj.catId, 0,
				is_constraint ? indxinfo->indexconstraint :
				indxinfo->dobj.dumpId);

	destroyPQExpBuffer(q);
	destroyPQExpBuffer(delq);
	destroyPQExpBuffer(labelq);
}
