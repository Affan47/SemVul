embHitlistDel(EmbPHitlist *ptr)
{
    ajuint x = 0;

    if(!(*ptr))
    {
	ajWarn("Null pointer passed to embHitlistDel");

	return;
    }

    if((*ptr)->Class)
	ajStrDel(&(*ptr)->Class);

    if((*ptr)->Architecture)
	ajStrDel(&(*ptr)->Architecture);

    if((*ptr)->Topology)
	ajStrDel(&(*ptr)->Topology);

    if((*ptr)->Fold)
	ajStrDel(&(*ptr)->Fold);

    if((*ptr)->Superfamily)
	ajStrDel(&(*ptr)->Superfamily);

    if((*ptr)->Family)
	ajStrDel(&(*ptr)->Family);

    if((*ptr)->Model)
	ajStrDel(&(*ptr)->Model);

    for(x=0;x<(*ptr)->N; x++)
	if((*ptr)->hits[x])
	    embHitDel(&(*ptr)->hits[x]);

    if((*ptr)->hits)
	AJFREE((*ptr)->hits);

    if(*ptr)
	AJFREE(*ptr);

    *ptr = NULL;

    return;
}
