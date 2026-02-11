embMatProtDelInt(EmbPMatPrints *s)
{
    ajint n;
    ajint i;
    ajint j;

    n = (*s)->n;

    for(i=0;i<n;++i)
	for(j=0;j<26;++j)
	    AJFREE((*s)->matrix[i][j]);

    AJFREE((*s)->matrix);
    AJFREE((*s)->len);
    AJFREE((*s)->thresh);
    AJFREE((*s)->max);

    ajStrDel(&(*s)->cod);
    ajStrDel(&(*s)->acc);
    ajStrDel(&(*s)->tit);
    AJFREE(*s);

    return;
}
