md_enable( MD_HANDLE h, int algo )
{
    struct md_digest_list_s *r, *ac;

    for( ac=h->list; ac; ac = ac->next )
	if( ac->algo == algo )
	    return ;

    do {
	for(r = digest_list; r; r = r->next )
	    if( r->algo == algo )
		break;
    } while( !r && load_digest_module () );
    if( !r ) {
	log_error("md_enable: algorithm %d not available\n", algo );
	return;
    }

    ac = h->secure? xmalloc_secure( sizeof *ac + r->contextsize
					       - sizeof(r->context) )
		  : xmalloc( sizeof *ac + r->contextsize
					       - sizeof(r->context) );
    *ac = *r;
    ac->next = h->list;
    h->list = ac;

    (*ac->init)( &ac->context.c );
}
