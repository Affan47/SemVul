cirdna_TextRuler(float Start, float End, ajint GapSize,
			      float TextLength, float TextHeight,
			      const AjPStr PosTicks, ajint NumGroups,
			      const ajint *NumLabels)
{
    ajint i;
    ajint j;
    const AjPStr token;
    AjPStr string;
    float charsize;
    float minsize = 100.0;

    string = ajStrNew();

    ajStrFromInt(&string, (ajint)Start);
    charsize = ajGraphicsCalcCharsize(0, 0, TextLength, TextLength,
                                      ajStrGetPtr(string), TextHeight );
    if(charsize < minsize)
	minsize = charsize;

    for(i=GapSize; i<End; i+=GapSize)
	if(i>Start)
	{
	    ajStrFromInt(&string, i);
	    charsize = ajGraphicsCalcCharsize(0, 0, TextLength, TextLength,
                                              ajStrGetPtr(string), TextHeight );
	    if(charsize < minsize)
		minsize = charsize;
	}

    for(i=0; i<NumGroups; i++)
	for(j=0; j<NumLabels[i]; j++)
	    if(ajStrMatchCaseC(Style[i][j], "Tick") &&
	       ajStrMatchCaseC(PosTicks, "Out") )
	    {
		token = ajStrParseC(Name[i][j], ";");
		charsize = ajGraphicsCalcCharsize( 0, 0, TextLength,
                                                   TextLength,
                                                   ajStrGetPtr(token),
                                                   TextHeight );
		if(charsize < minsize)
		    minsize = charsize;
	    }

    ajStrDel(&string);

    return minsize;
}
