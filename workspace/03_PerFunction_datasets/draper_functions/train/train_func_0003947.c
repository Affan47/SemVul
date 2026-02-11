cellwidth_ptr_to_ptr(CELL *pstart, CELL *pend)
{
    CELL *p;
    unsigned width = 0;
    int ww;

    if(pstart)
      for(p = pstart; p < pend; p++){
	  ww = wcellwidth((UCS) p->c);
	  width += (ww >= 0 ? ww : 1);
      }

    return(width);
}
