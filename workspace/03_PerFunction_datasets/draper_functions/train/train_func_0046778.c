any_addrs_avail(long int starting_hint)
{
    register AddrScrn_Disp *dl;
    long lineno;


    lineno = starting_hint;
    for(dl=dlist(lineno);
	dl->type != Beginning;
	dl = dlist(--lineno)){
	if(dl->type == NoAbooks)
	  return 0;

	switch(dl->type){
	  case Simple:
	  case ListEnt:
	  case ListHead:
	  case ZoomEmpty:
	  case Title:
	  case ListClickHere:
	  case ClickHereCmb:
	    return 1;
	  default:
	    break;
	}
    }


    lineno = starting_hint;
    for(dl=dlist(lineno);
	dl->type != End;
	dl = dlist(++lineno)){
	if(dl->type == NoAbooks)
	  return 0;

	switch(dl->type){
	  case Simple:
	  case ListEnt:
	  case ListHead:
	  case ZoomEmpty:
	  case Title:
	  case ListClickHere:
	  case ClickHereCmb:
	    return 1;
	  default:
	    break;
	}
    }

    return 0;
}
