showorf_CalcProteinPos(ajint **ppos, AjPStr const *pseqs,
				   ajint len)
{
    ajint i;
    ajint j;

    ajint pos;
    ajint v;

    const char *p;


    for(i=0;i<3;++i)
    {
	pos = 0;
	v   = 1;

	p = ajStrGetPtr(pseqs[i]);
	while(p[pos]==' ')
	    ppos[i][pos++]=0;

	while(pos<len)
	{
	    if(p[pos]=='*')
	    {
		ppos[i][pos]=0;
		++pos;
		while(p[pos]==' ')
		{
		    ppos[i][pos] = 0;
		    ++pos;
		}
		v = 1;
		continue;
	    }

	    if(p[pos]!=' ')
	    {
		ppos[i][pos]=v+POFF;
		++pos;
		for(j=0;j<2 && p[pos];++j,++pos)
		    ppos[i][pos] = v;
		if(p[pos]==' ')
		    v = 1;
		else
		    ++v;
	    }
	    else
		ppos[i][pos++] = 0;
	}
    }


    for(i=3;i<6 && len;++i)
    {
	pos = len-1;
	v   = 1;

	p=ajStrGetPtr(pseqs[i]);
	while(p[pos]==' ')
	    ppos[i][pos--]=0;

	while(pos>-1)
	{
	    if(p[pos]=='*')
	    {
		ppos[i][pos]=0;
		--pos;
		while(p[pos]==' ')
		{
		    ppos[i][pos]=0;
		    --pos;
		}
		v = 1;
		continue;
	    }

	    if(p[pos]!=' ')
	    {
		ppos[i][pos]=v+POFF;
		--pos;
		for(j=0;j<2 && p[pos];++j,--pos)
		    ppos[i][pos] = v;
		if(pos<0) continue;
		if(p[pos]==' ')
		    v = 1;
		else
		    ++v;
	    }
	    else
		ppos[i][pos--] = 0;
	}
    }

    return;
}
