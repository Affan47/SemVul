namedlabel()
{
    struct symstruct *symptr;

    gs2name[1] = 0xFF;
    if ((symptr = findlorg(gs2name + 1)) == NULL)
    {
	symptr = addglb(gs2name + 1, vtype);
	symptr->flags = LABELLED;
    }
    if (symptr->indcount < 2)
    {
	symptr->indcount = 2;
	symptr->offset.offlabel = gethighlabel();
	if (namedfirst == NULL)
	    namedfirst = symptr;
	else
	    namedlast->type = (struct typestruct *) symptr;
	namedlast = symptr;
	symptr->type = NULL;
    }
    return symptr;
}
