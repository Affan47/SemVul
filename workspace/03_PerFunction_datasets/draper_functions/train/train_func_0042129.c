embGrpProgsListDel(AjPList *progslist)
{
    EmbPGroupProg gl;
    AjIList piter;

    if(!*progslist)
        return;

    piter = ajListIterNew(*progslist);

    while((gl = ajListIterGet(piter)) != NULL)
    {
        embGrpProgDel(&gl);
    }

    ajListIterDel(&piter);
    ajListFree(progslist);

    return;
}
