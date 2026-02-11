ajSqlrowiterNew(AjPSqlstatement sqls)
{
    AjISqlrow sqli = NULL;

    if(!sqls)
        return NULL;

    if(!sqls->SelectedRows)
        return NULL;

    if(!sqls->Columns)
        return NULL;

    AJNEW0(sqli);

    sqli->Sqlstatement = ajSqlstatementNewRef(sqls);

    sqli->Sqlrow = ajSqlrowNew(sqls->Columns);

    sqli->Current = 0;

    return sqli;
}
