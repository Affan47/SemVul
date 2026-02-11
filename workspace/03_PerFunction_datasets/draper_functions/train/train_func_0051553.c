emowse_seq_search(const AjPStr substr, AjPStr *str)
{
    const char *p;
    char *q;
    char* s;
    static AjPStr t = NULL;

    if(!t)
	t = ajStrNew();

    p = ajStrGetPtr(substr);
    ajStrAssignC(&t,p);
    q = ajStrGetuniquePtr(&t);
    s = ajStrGetuniquePtr(str);

    if(!strncmp(s,"B-",2))
    {
	if(!emowse_msearch(q,s+2,ajFalse))
	    return ajFalse;
    }
    else if(!strncmp(s,"N-",2))
    {
	if(!emowse_msearch(q,s+2,ajTrue))
	    return ajFalse;
    }
    else if(!strncmp(s,"C-",2))
    {
	emowse_mreverse(s+2);
	emowse_mreverse(q);

	if(!emowse_msearch(q,s+2,ajTrue))
	    return ajFalse;
    }
    else if(!strncmp(s,"*-",2))
    {
	if(!emowse_msearch(q,s+2,ajFalse))
	    return ajTrue;
	emowse_mreverse(s+2);

	if(!emowse_msearch(q,s+2,ajFalse))
	    return ajFalse;
    }

    return ajTrue;
}
