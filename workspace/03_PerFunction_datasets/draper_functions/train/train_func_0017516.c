grpRelationsListClear(AjPList relslist)
{
    EmbPGroupRelation gl;

    while(ajListGetLength(relslist))
    {
	ajListPop(relslist, (void**) &gl);
        ajStrDel(&(gl->type));
	ajStrDel(&(gl->qual));
	ajStrDel(&(gl->acdgroup));
	ajStrDel(&(gl->id));
	ajStrDel(&(gl->namespace));
	ajStrDel(&(gl->name));
	AJFREE(gl);
    }

    return;
}
