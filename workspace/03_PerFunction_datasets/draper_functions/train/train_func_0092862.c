dumpTableSecLabel(Archive *fout, TableInfo *tbinfo, const char *reltypename)
{
	SecLabelItem *labels;
	int			nlabels;
	int			i;
	PQExpBuffer query;
	PQExpBuffer target;


	if (no_security_labels)
		return;


	if (dataOnly)
		return;


	nlabels = findSecLabels(fout,
							tbinfo->dobj.catId.tableoid,
							tbinfo->dobj.catId.oid,
							&labels);


	if (nlabels <= 0)
		return;

	query = createPQExpBuffer();
	target = createPQExpBuffer();

	for (i = 0; i < nlabels; i++)
	{
		const char *colname;
		const char *provider = labels[i].provider;
		const char *label = labels[i].label;
		int			objsubid = labels[i].objsubid;

		resetPQExpBuffer(target);
		if (objsubid == 0)
		{
			appendPQExpBuffer(target, "%s %s", reltypename,
							  fmtId(tbinfo->dobj.name));
		}
		else
		{
			colname = getAttrName(objsubid, tbinfo);

			appendPQExpBuffer(target, "COLUMN %s", fmtId(tbinfo->dobj.name));
			appendPQExpBuffer(target, ".%s", fmtId(colname));
		}
		appendPQExpBuffer(query, "SECURITY LABEL FOR %s ON %s IS ",
						  fmtId(provider), target->data);
		appendStringLiteralAH(query, label, fout);
		appendPQExpBuffer(query, ";\n");
	}
	if (query->len > 0)
	{
		resetPQExpBuffer(target);
		appendPQExpBuffer(target, "%s %s", reltypename,
						  fmtId(tbinfo->dobj.name));
		ArchiveEntry(fout, nilCatalogId, createDumpId(),
					 target->data,
					 tbinfo->dobj.namespace->dobj.name,
					 NULL, tbinfo->rolname,
					 false, "SECURITY LABEL", SECTION_NONE,
					 query->data, "", NULL,
					 &(tbinfo->dobj.dumpId), 1,
					 NULL, NULL);
	}
	destroyPQExpBuffer(query);
	destroyPQExpBuffer(target);
}
