embPropProt1to3(AjPSeq seq, ajint pad)
{
    const char *p;
    const char *p3;
    AjPStr temp;
    ajint i;

    temp = ajStrNewRes(ajSeqGetLen(seq)*3 + pad+1);


    for(i=0; i<pad; i++)
	ajStrAppendC(&temp, " ");


    for(p=ajSeqGetSeqC(seq); *p; p++)
    {
	if(*p == '*')
	    ajStrAppendC(&temp, "***");
	else if(*p == '.')
	    ajStrAppendC(&temp, "...");
	else if(*p == '-')
	    ajStrAppendC(&temp, "---");
	else if(!isalpha((ajint)*p))
	    ajStrAppendC(&temp, "???");
	else
	{
	    p3 = embPropCharToThree(*p);
	    ajStrAppendK(&temp, *p3);
	    ajStrAppendK(&temp, *(p3+1));
	    ajStrAppendK(&temp, *(p3+2));
	}
    }

    return temp;
}
