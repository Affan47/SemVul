dumpTableData(Archive *fout, TableDataInfo *tdinfo)
{
	TableInfo  *tbinfo = tdinfo->tdtable;
	PQExpBuffer copyBuf = createPQExpBuffer();
	DataDumperPtr dumpFn;
	char	   *copyStmt;

	if (!dump_inserts)
	{

		dumpFn = dumpTableData_copy;

		appendPQExpBuffer(copyBuf, "COPY %s ",
						  fmtId(tbinfo->dobj.name));
		appendPQExpBuffer(copyBuf, "%s %sFROM stdin;\n",
						  fmtCopyColumnList(tbinfo),
					  (tdinfo->oids && tbinfo->hasoids) ? "WITH OIDS " : "");
		copyStmt = copyBuf->data;
	}
	else
	{

		dumpFn = dumpTableData_insert;
		copyStmt = NULL;
	}

	ArchiveEntry(fout, tdinfo->dobj.catId, tdinfo->dobj.dumpId,
				 tbinfo->dobj.name, tbinfo->dobj.namespace->dobj.name,
				 NULL, tbinfo->rolname,
				 false, "TABLE DATA", SECTION_DATA,
				 "", "", copyStmt,
				 tdinfo->dobj.dependencies, tdinfo->dobj.nDeps,
				 dumpFn, tdinfo);

	destroyPQExpBuffer(copyBuf);
}
