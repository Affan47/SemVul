ajDmxScophitCopy(AjPScophit *Pto, const AjPScophit from)
{
    if(!Pto || !*Pto)
        return ajFalse;

    if(!from)
        return ajFalse;

    (*Pto)->Type = from->Type;
    ajStrAssignS(&(*Pto)->Class, from->Class);
    ajStrAssignS(&(*Pto)->Architecture, from->Architecture);
    ajStrAssignS(&(*Pto)->Topology, from->Topology);
    ajStrAssignS(&(*Pto)->Fold, from->Fold);
    ajStrAssignS(&(*Pto)->Superfamily, from->Superfamily);
    ajStrAssignS(&(*Pto)->Family, from->Family);
    ajStrAssignS(&(*Pto)->Seq, from->Seq);
    ajStrAssignS(&(*Pto)->Acc, from->Acc);
    ajStrAssignS(&(*Pto)->Spr, from->Spr);
    ajStrAssignS(&(*Pto)->Dom, from->Dom);
    ajStrAssignS(&(*Pto)->Typeobj, from->Typeobj);
    ajStrAssignS(&(*Pto)->Typesbj, from->Typesbj);
    ajStrAssignS(&(*Pto)->Model, from->Model);
    ajStrAssignS(&(*Pto)->Alg, from->Alg);
    ajStrAssignS(&(*Pto)->Group, from->Group);
    (*Pto)->Start        = from->Start;
    (*Pto)->End          = from->End;
    (*Pto)->Rank         = from->Rank;
    (*Pto)->Score        = from->Score;
    (*Pto)->Eval         = from->Eval;
    (*Pto)->Pval         = from->Pval;
    (*Pto)->Target       = from->Target;
    (*Pto)->Target2      = from->Target2;
    (*Pto)->Priority     = from->Priority;
    (*Pto)->Sunid_Family = from->Sunid_Family;

    return ajTrue;
}
