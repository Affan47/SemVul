ajNamDbGetDbaliasTest(const AjPStr dbname, AjPStr* dbalias)
{

    const NamPEntry data;
    const AjPTable dbtable;
    const AjPStr dbval = NULL;

    data = ajTableFetchS(namDbMasterTable, dbname);

    if(!data)
        return ajFalse;

    dbtable = (const AjPTable) data->data;

    dbval = ajTableFetchC(dbtable, "dbalias");

    if(ajStrGetLen(dbval))
	ajStrAssignS(dbalias, dbval);
    else
    {
        ajStrAssignS(dbalias, dbname);
        ajStrFmtLower(dbalias);
    }

    return ajTrue;
}
