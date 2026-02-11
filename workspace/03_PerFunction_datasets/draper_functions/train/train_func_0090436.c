SITEunlink(sp)
    SITE		*sp;
{
    if (sp->Next != NOSITE || sp->Prev != NOSITE
     || (SITEhead != NOSITE && sp == &Sites[SITEhead]))
	SITEcount--;

    if (sp->Next != NOSITE)
	Sites[sp->Next].Prev = sp->Prev;
    else if (SITEtail != NOSITE && sp == &Sites[SITEtail])
	SITEtail = sp->Prev;

    if (sp->Prev != NOSITE)
	Sites[sp->Prev].Next = sp->Next;
    else if (SITEhead != NOSITE && sp == &Sites[SITEhead])
	SITEhead = sp->Next;

    sp->Next = sp->Prev = NOSITE;
}
