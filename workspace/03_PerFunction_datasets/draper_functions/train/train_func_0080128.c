ajSeqcvtNewStrAsym (const AjPPStr basearray, ajint numbases,
				 const AjPPStr matchbases, ajint nummatch)
{
    static AjPSeqCvt ret;
    ajint i;


    AJNEW0(ret);
    ret->len = numbases;
    ret->nclabels = numbases;
    ret->nrlabels = nummatch;
    ret->size = CHAR_MAX - CHAR_MIN + 1;
    ret->table = AJCALLOC0(ret->size, sizeof(char));
    ret->bases = ajStrNew();
    ret->missing = 0;


    AJCNEW0(ret->rlabels, nummatch);

    for(i=0; i<nummatch; i++)
	ret->rlabels[i] = ajStrNew();

    for(i=0; i<nummatch; i++)
	ajStrAssignS(&ret->rlabels[i], matchbases[i]);


    AJCNEW0(ret->clabels, numbases);

    for(i=0; i<numbases; i++)
	ret->clabels[i] = ajStrNew();

    for(i=0; i<numbases; i++)
	ajStrAssignS(&ret->clabels[i], basearray[i]);


    for(i=0; i<numbases; i++)
    {

	ajStrAppendK(&ret->bases, ajStrGetCharFirst(basearray[i]));
	ret->table[toupper((ajint) ajStrGetCharFirst(basearray[i]))] =
	    ajSysCastItoc(i+1);
	ret->table[tolower((ajint) ajStrGetCharFirst(basearray[i]))] =
	    ajSysCastItoc(i+1);
    }

    return ret;
}
