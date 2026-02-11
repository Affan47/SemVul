embPropCalcMolwtMod(const char *s, ajint start, ajint end,
			   EmbPPropMolwt const *mwdata, AjBool mono,
			   double nmass, double cmass)
{
    const char *p;
    double sum;
    ajint i;
    ajint len;
    ajint idx;
    double mw = 0.;

    len = end - start + 1;

    p = s + start;
    sum = 0.0;

    for(i=0;i<len;++i)
    {
	idx = ajBasecodeToInt(toupper((ajint)p[i]));
	mw = (mono) ? mwdata[idx]->mono : mwdata[idx]->average;

	sum += mw;
    }

    return sum + nmass + cmass;
}
