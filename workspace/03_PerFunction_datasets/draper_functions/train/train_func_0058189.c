ajSqlcolumnNumberGetValue(const AjPSqlrow sqlr,
                                 ajuint column,
                                 void **Pvalue,
                                 ajulong *Plength)
{
    if(!sqlr)
        return ajFalse;

    if(column >= sqlr->Columns)
        return ajFalse;

    if(!Pvalue)
        return ajFalse;

    if(!Plength)
        return ajFalse;

    *Pvalue = ajVoidGet(sqlr->Values, column);

    *Plength = ajLongGet(sqlr->Lengths, column);

    return ajTrue;
}
