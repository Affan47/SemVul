getTableData(TableInfo *tblinfo, int numTables, bool oids)
{
	int			i;

	for (i = 0; i < numTables; i++)
	{

		if (tblinfo[i].relkind == RELKIND_VIEW)
			continue;

		if (tblinfo[i].relkind == RELKIND_SEQUENCE)
			continue;

		if (tblinfo[i].dobj.dump)
		{
			TableDataInfo *tdinfo;

			tdinfo = (TableDataInfo *) malloc(sizeof(TableDataInfo));

			tdinfo->dobj.objType = DO_TABLE_DATA;


			tdinfo->dobj.catId.tableoid = 0;
			tdinfo->dobj.catId.oid = tblinfo[i].dobj.catId.oid;
			AssignDumpId(&tdinfo->dobj);
			tdinfo->dobj.name = tblinfo[i].dobj.name;
			tdinfo->dobj.namespace = tblinfo[i].dobj.namespace;
			tdinfo->tdtable = &(tblinfo[i]);
			tdinfo->oids = oids;
			addObjectDependency(&tdinfo->dobj, tblinfo[i].dobj.dumpId);
		}
	}
}
