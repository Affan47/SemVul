ajSqlcolumnToStr(AjPSqlrow sqlr, AjPStr *Pvalue)
{
    void *value = NULL;

    ajulong length = 0;

    if(!sqlr)
        return ajFalse;

    if(!Pvalue)
        return ajFalse;

    if(sqlr->Current >= sqlr->Columns)
        return ajFalse;

    ajStrAssignClear(Pvalue);

    if(ajSqlcolumnGetValue(sqlr, &value, &length))
    {
        if(value == NULL)
            return ajFalse;

        if(length > UINT_MAX)
            return ajFalse;

        ajStrAssignLenC(Pvalue, (char *) value, (size_t) length);

        return ajTrue;
    }

    return ajFalse;
}
