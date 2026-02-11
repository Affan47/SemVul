eprimer3_tableget(const char *key1, ajint number,
				const char *key2,
                                const AjPTable table)
{
    AjPStr fullkey = NULL;
    AjPStr keynum  = NULL;
    const AjPStr value   = NULL;

    ajStrAssignC(&fullkey, key1);

    if(number > 0)
    {
        ajStrAppendC(&fullkey, "_");
        ajStrFromInt(&keynum, number);
        ajStrAppendS(&fullkey, keynum);
    }

    if(strcmp(key2, ""))
        ajStrAppendC(&fullkey, "_");

    ajStrAppendC(&fullkey, key2);
    ajDebug("Constructed key=%S\n", fullkey);
    value = ajTableFetchS(table, fullkey);


    ajStrDel(&fullkey);
    ajStrDel(&keynum);

    return value;
}
