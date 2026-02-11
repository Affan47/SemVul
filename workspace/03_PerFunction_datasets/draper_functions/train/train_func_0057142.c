ajFeatGfftagsDel(AjPFeatGfftags *Pthys)
{
    AjPFeatGfftags thys;

    if(!Pthys)
        return;
    if(!*Pthys)
        return;

    thys = *Pthys;

    ajStrDel(&thys->Id);
    ajStrDel(&thys->Name);
    ajStrDel(&thys->Alias);
    ajStrDel(&thys->Parent);
    ajStrDel(&thys->Target);
    ajStrDel(&thys->Gap);
    ajStrDel(&thys->DerivesFrom);
    ajStrDel(&thys->Note);
    ajStrDel(&thys->Dbxref);
    ajStrDel(&thys->OntologyTerm);
    ajStrDel(&thys->IsCircular);

    AJFREE(*Pthys);

    return;
}
