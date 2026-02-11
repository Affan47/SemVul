tmap_tm_in_vector(const ajint *start, const ajint *stopp,
			       ajint max,
			       ajint starttmp, ajint stopptmp)
{
    ajint i;
    ajint temp;

    temp = 0;
    for(i=1; i<=max; i++)
	if((abs(start[i]-starttmp)<7) && (abs(stopp[i]-stopptmp)<7))
	    temp = 1;

    return temp;
}
