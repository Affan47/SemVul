showorf_DoTrans(const AjPStr s, const AjPStr r, ajint n, ajint len,
			    AjPStr *pseqs, const AjPCod codon)
{
    const char *p;
    char *q;

    ajint po;

    ajint i;
    ajint c;
    ajint idx;

    char tri[4];


    if(n<3)
    {
	p  = ajStrGetPtr(s);
	po = n%3;
    }
    else
    {
	p  = ajStrGetPtr(r);
	po = len%3;
	po -= n%3;
	if(po<0)
	    po += 3;
    }

    for(i=0,q=ajStrGetuniquePtr(&pseqs[n]);i<po;++i)
	q[i] = ' ';


    for(i=po,c=0,tri[3]='\0';i<len;++i,++c)
    {
	if(c%3 || len-i<3)
	{
	    q[i] = ' ';
	    continue;
	}

	tri[0] = (char)toupper((int)p[i]);
	tri[1] = (char)toupper((int)p[i+1]);
	tri[2] = (char)toupper((int)p[i+2]);
	if(!strcmp(tri,"NNN"))
	{
	    q[i] = 'X';
	    continue;
	}
	idx = ajCodIndexC(tri);
	if(codon->aa[idx]==27)
	    q[i] = '*';
	else
	    q[i] = (char)(codon->aa[idx]+'A');
    }

    return;
}
