namDbtablePutAttrS(AjPTable dbtable, AjPStr *Pattribute,
                                 AjPStr *Pvalue)
{
    void *oldval;
    NamPAttr attr;
    AjPList fdlist = NULL;

    attr  = ajTableFetchmodS(namDbAttrTable, *Pattribute);
    namUser("store db attr '%S' => '%S'\n", *Pattribute, *Pvalue);

    switch(attr->Type)
    {
        case ATTR_LIST:
            fdlist = ajTableFetchmodS(dbtable, *Pattribute);

            if(!fdlist)
            {
                fdlist = ajListstrNew();
                ajTablePut(dbtable, (AjPStr) *Pattribute, (AjPList) fdlist);
                *Pattribute = NULL;
            }
            else
                ajStrDel(Pattribute);

            ajListstrPushAppend(fdlist, *Pvalue);
            break;

        default:
            oldval = ajTablePut(dbtable, (AjPStr) *Pattribute,
                                (AjPStr) *Pvalue);
            if(oldval)
                ajWarn("duplicate db keyword value for '%S' = '%S'",
                       *Pattribute, (AjPStr) oldval);

            *Pattribute = NULL;
            break;
    }

    *Pvalue = NULL;

    return ajTrue;
}
