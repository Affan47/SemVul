bamHeaderTotable(const AjPList dict, const char type[2],
                                 const char key_tag[2],
                                 const char value_tag[2])
{
    AjPTable tbl = NULL;
    BamPHeaderLine hline = NULL;
    AjIList k;
    BamPHeaderTag key;
    BamPHeaderTag value;

    tbl = ajTablecharNew(512);

    if(dict == 0)
        return tbl;

    k = ajListIterNewread(dict);

    while(!ajListIterDone(k))
    {
        hline = ajListIterGet(k);

        if(hline->type[0]!=type[0] || hline->type[1]!=type[1])
            continue;

        key   = bamHeaderLineHasTag(hline,key_tag);
        value = bamHeaderLineHasTag(hline,value_tag);

        if(!key || !value)
            continue;

        if(ajTablePut(tbl, key->value, value->value))
            ajWarn("[bamHeaderTotable] The key %s not unique.\n",
                   key->value);
    }

    ajListIterDel(&k);

    return tbl;
}
