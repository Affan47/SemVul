embPatBMHSearch(const AjPStr str, const AjPStr pat,
		      ajuint slen, ajuint plen, const ajint *skip,
		      ajuint start, AjBool left, AjBool right, AjPList l,
		      const AjPStr name, ajuint begin)
{
    ajuint i;
    ajuint j;
    ajuint jj;
    ajuint k = 0;
    const char *p;
    const char *q;
    AjBool flag;
    ajuint count;

    if(left && start)
	return 0;

    p = ajStrGetPtr(str);
    q = ajStrGetPtr(pat);

    flag = ajTrue;
    count = 0;

    i = start+(plen-1);
    jj = plen;
    j = jj-1;

    while(flag)
    {
	while(jj>0 && i<slen)
	{
	    k = i;

	    while(jj>0 && p[k]==q[j])
	    {
		--k;
		--j;
		--jj;
	    }

	    if(jj>0)
	    {
		i += skip[(ajuint)p[i]];
		jj = plen;
		j = jj-1;
	    }
	}

	if(jj == 0)
	{
	    if(left && k+1)
		return 0;

	    if(!right || (right && k+1+plen==slen))
	    {
		++count;
		embPatPushHit(l,name,k+1,plen,begin,0);
	    }

	    i = start+(plen-1)+k+2;
	    jj = plen;
	    j = jj-1;

	}
	else
	    flag=ajFalse;
    }

    return count;
}
