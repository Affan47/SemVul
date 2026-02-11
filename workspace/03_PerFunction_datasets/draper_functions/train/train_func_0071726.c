prettyseq_makeRuler(ajint len, ajint begin, char *ruler,
				ajint *npos)
{
    ajint i;

    for(i=0;i<len;++i)
    {
	npos[i] = i+begin;

	if(!((i+begin)%10))
	    ruler[i] = '|';
	else
	    ruler[i] = '-';
    }

    return;
}
