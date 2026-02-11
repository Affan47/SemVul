cachedbfetch_SetDbtype(dbPinfo dbinfo, AjPTable dbtypes)
{
    char** keys = NULL;
    ajuint i;
    ajuint n;


    ajTableToarrayKeys(dbtypes, (void***)&keys);

    n = (ajuint) ajTableGetLength(dbtypes);

    for(i=0;i<n;i++)
    {
	if (i>0)
	    ajStrAppendC(&dbinfo->dbtype, ", ");

	ajStrAppendC(&dbinfo->dbtype, keys[i]);
    }

    if(!n)
	ajWarn("No dbtype found for db %S", dbinfo->displayname);

    AJFREE(keys);

    return;
}
