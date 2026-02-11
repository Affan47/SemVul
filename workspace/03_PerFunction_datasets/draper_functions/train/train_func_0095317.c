baseadaptorRetrieveAllStatement(
    EnsPBaseadaptor ba,
    const AjPStr tablename,
    const AjPStr columnname,
    AjPStr *Pstatement)
{
    if (!ba)
        return ajFalse;

    if (!tablename)
        return ajFalse;

    if (!Pstatement)
        return ajFalse;

    if (*Pstatement)
        ajStrAssignClear(Pstatement);
    else
        *Pstatement = ajStrNew();

    if (columnname && ajStrGetLen(columnname))
        ajFmtPrintAppS(Pstatement,
                       "SELECT %S.%S FROM %S",
                       tablename,
                       columnname,
                       tablename);
    else
        ajFmtPrintAppS(Pstatement,
                       "SELECT %S.%S_id FROM %S",
                       tablename,
                       tablename,
                       tablename);

    return ajTrue;
}
