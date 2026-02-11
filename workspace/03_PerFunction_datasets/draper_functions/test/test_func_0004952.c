cirdna_HorTextPileLengthMax(const AjPStr Name2, ajint NumNames)
{
    float stringLength;
    float maxLength;
    ajint i;
    const AjPStr token;

    maxLength = 0.0;
    for(i=0; i<NumNames; i++)
    {
	if(i==0)
	    token = ajStrParseC(Name2, ";");
	else
	    token = ajStrParseC(NULL, ";");
	stringLength = ajGraphicsCalcTextlengthS(token);

	if(stringLength>maxLength)
	    maxLength = stringLength;
    }

    return maxLength;
}
