ajTableDelValdel(AjPTable* Ptable,
                      void (*valdel)(void** Pvalue))
{
    AjPTable thys;

    if(!Ptable)
        return;
    if(!*Ptable)
        return;

    thys = *Ptable;

    if(!thys->Use)
        ajErr("trying to delete unused table");

    --thys->Use;

    if(!thys->Use)
    {
        thys->Fvaldel = valdel;

        ajTableClearDelete(thys);

        AJFREE(thys->Buckets);
        AJFREE(*Ptable);
    }

    *Ptable = NULL;

    return;
}
