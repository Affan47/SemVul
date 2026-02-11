dumpComment(Archive *fout, const char *target,
			const char *namespace, const char *owner,
			CatalogId catalogId, int subid, DumpId dumpId)
{
	CommentItem *comments;
	int			ncomments;


	if (strncmp(target, "LARGE OBJECT ", 13) != 0)
	{
		if (dataOnly)
			return;
	}
	else
	{
		if (schemaOnly)
			return;
	}


	ncomments = findComments(fout, catalogId.tableoid, catalogId.oid,
							 &comments);


	while (ncomments > 0)
	{
		if (comments->objsubid == subid)
			break;
		comments++;
		ncomments--;
	}


	if (ncomments > 0)
	{
		PQExpBuffer query = createPQExpBuffer();

		appendPQExpBuffer(query, "COMMENT ON %s IS ", target);
		appendStringLiteralAH(query, comments->descr, fout);
		appendPQExpBuffer(query, ";\n");


		ArchiveEntry(fout, nilCatalogId, createDumpId(),
					 target, namespace, NULL, owner,
					 false, "COMMENT", SECTION_NONE,
					 query->data, "", NULL,
					 &(dumpId), 1,
					 NULL, NULL);

		destroyPQExpBuffer(query);
	}
}
