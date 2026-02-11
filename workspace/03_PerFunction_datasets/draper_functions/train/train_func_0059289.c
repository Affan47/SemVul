ajHistDataAdd(AjPHist thys, ajuint indexnum, PLFLT *data)
{
    if(indexnum >= thys->numofdatapoints)
    {
	ajErr("Histograms can only be allocated from 0 to %d. NOT %u",
	      thys->numofdatapoints-1,indexnum);

	return;
    }

    if(!thys->hists[indexnum]->data)
	thys->numofsets++;

    thys->hists[indexnum]->data = data;

    return;
}
