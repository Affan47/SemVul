ajDomainCopy(AjPDomain *Pto, const AjPDomain from)
{
    ajuint n = 0U;


    if(!from)
        return ajFalse;

    if((*Pto))
        ajDomainDel(Pto);

    if(from->Type == ajEDomainTypeSCOP)
        n = from->Scop->Number;
    else
        n = from->Cath->NSegment;

    (*Pto) = ajDomainNew(n, from->Type);

    (*Pto)->Type = from->Type;

    if(from->Type == ajEDomainTypeSCOP)
        ajScopCopy(&((*Pto)->Scop), from->Scop);
    else
        ajCathCopy(&((*Pto)->Cath), from->Cath);

    return ajTrue;
}
