ensGvvariationValidationsToSet(ajuint gvvvbf, AjPStr *Pgvvvset)
{
    register ajuint i = 0U;

    if (*Pgvvvset)
        ajStrAssignClear(Pgvvvset);
    else
        *Pgvvvset = ajStrNew();

    for (i = 1U; gvvariationKValidation[i]; i++)
        if (gvvvbf & (1U << i))
        {
            ajStrAppendC(Pgvvvset, gvvariationKValidation[i]);
            ajStrAppendC(Pgvvvset, ",");
        }


    if (ajStrGetLen(*Pgvvvset) > 0U)
        ajStrCutEnd(Pgvvvset, 1);

    return ajTrue;
}
