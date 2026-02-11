ensStorableIsStored(const EnsPStorable storable,
                           const EnsPDatabaseconnection dbc)
{
    if (!storable)
        return ajFalse;

    if (!dbc)
        return ajFalse;

    if (storable->Identifier && (!storable->Adaptor))
        return ajFalse;

    if (storable->Adaptor && (!storable->Identifier))
        return ajFalse;

    if ((!storable->Identifier) && (!storable->Adaptor))
        return ajFalse;


    return ajFalse;
}
