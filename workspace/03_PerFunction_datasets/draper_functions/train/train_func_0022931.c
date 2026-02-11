ajNamServer(const AjPStr name)
{
    const NamPEntry fnew = NULL;


    fnew = ajTableFetchS(namSvrMasterTable, name);

    if(fnew)
    {

	return ajTrue;
    }


    return ajFalse;
}
