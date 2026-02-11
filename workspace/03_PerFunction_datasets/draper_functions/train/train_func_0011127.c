stepPosn(srcPosn* p)
{
    srcLine *L = p->Line;

    p->idx++;

    if( L->line[p->idx] == '\0' ) {


	for( L=L->next; L != (srcLine *)NULL && L->comment; L=L->next )
	    continue;


	if( L != (srcLine *)NULL && L->contin ) {
	    p->Line = L;
	    p->idx = L->start_index;
	}
    }
}
