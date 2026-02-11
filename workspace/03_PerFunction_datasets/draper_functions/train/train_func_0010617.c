edialign_predFrontier(edialignCLOSURE *clos,
				   ajint x, ajint i, ajint y)
{
    ajint n;
    ajint k;

    n = clos->seq[x].aligSetNbr[i];

    if(n == 0)
    {
	k = clos->seq[x].predAligSetPos[i];
	if(k > 0)
	    n = clos->seq[x].aligSetNbr[k];
    }

    if(n > 0)
	return(clos->predFrontier[n][y]);

    return(0);
}
