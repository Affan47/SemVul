showFillREuprightSort(const void* a, const void* b)
{
    ajint res;

    res = (*(EmbPShowREsite const *)b)->pos -
	(*(EmbPShowREsite const *)a)->pos;


    if(!res)
	res = ajStrGetLen((*(EmbPShowREsite const *)b)->name) -
	    ajStrGetLen((*(EmbPShowREsite const *)a)->name);

    return res;
}
