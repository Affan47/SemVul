ajNamSvrTest(const AjPStr svrname)
{
    const NamPEntry data;

    data = ajTableFetchS(namSvrMasterTable, svrname);

    if(!data)
	return ajFalse;

    return ajTrue;
}
