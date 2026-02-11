embGrpRelationsListDel(AjPList *relslist)
{
    EmbPGroupRelation gl;
    AjIList piter;

    piter = ajListIterNew(*relslist);

    while((gl = ajListIterGet(piter)) != NULL)
    {
	ajStrDel(&(gl->type));
	ajStrDel(&(gl->qual));
	ajStrDel(&(gl->acdgroup));
	ajStrDel(&(gl->id));
	ajStrDel(&(gl->namespace));
	ajStrDel(&(gl->name));
	AJFREE(gl);
    }

    ajListIterDel(&piter);
    ajListFree(relslist);

    return;
}
