pprints(int x, int y)
{
    register int i;
    register int j;

    if(x < y){
	for(i = x;i <= y; ++i){
	    for(j = 0; j < term.t_ncol; j++){
		pscreen[i]->v_text[j].c = ' ';
		pscreen[i]->v_text[j].a = 0;
	    }
        }
    }
    else{
	for(i = x;i >= y; --i){
	    for(j = 0; j < term.t_ncol; j++){
		pscreen[i]->v_text[j].c = ' ';
		pscreen[i]->v_text[j].a = 0;
	    }
        }
    }
    ttrow = y;
    ttcol = 0;
}
