ajCodIndexC(const char *codon)
{
    const char *p;
    ajint  sum;
    ajint c;

    p   = codon;
    sum = 0;

    if(!(c=*(p++)))
	return -1;

    sum += (ajCodBase(toupper(c))<<4);

    if(!(c=*(p++)))
	return -1;

    sum += (ajCodBase(toupper(c))<<2);

    if(!(c=*p))
	return -1;

    sum += ajCodBase(toupper(c));

    return sum;
}
