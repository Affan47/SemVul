ajHistSetmultiPattern(AjPHist thys, ajuint indexnum, ajint style)
{
    if(indexnum >= thys->numofdatapoints)
    {
	ajErr("Histograms can only be allocated from 0 to %d. NOT %u",
	      thys->numofdatapoints-1,indexnum);

	return;
    }

    thys->hists[indexnum]->pattern = style;

    return;
}
