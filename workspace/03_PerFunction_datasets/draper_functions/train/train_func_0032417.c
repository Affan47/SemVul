dbxtax_ParseMerged(AjPFile mergefile)
{
    AjPStr line = NULL;
    AjPStr oldid = NULL;
    AjPStr newid = NULL;
    AjPStr record = NULL;
    AjPStrTok handle = NULL;

    mergeTable = ajTablestrNew(20000);

    while(ajReadlineTrim(mergefile, &line))
    {
        ajStrTokenAssignC(&handle, line, "\t|");
        ajStrTokenNextParse(handle, &oldid);
        ajStrTokenNextParse(handle, &newid);
        record = ajTableFetchmodS(mergeTable, newid);
        if(!record)
        {
            ajTablePut(mergeTable, ajStrNewS(newid), ajStrNewS(oldid));
        }
        else
        {
            ajStrAppendK(&record, ' ');
            ajStrAppendS(&record, oldid);
        }
    }

    ajStrTokenDel(&handle);
    ajStrDel(&newid);
    ajStrDel(&oldid);
    ajStrDel(&line);

    return;
}
