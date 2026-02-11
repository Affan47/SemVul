bibl_checkrefid( bibl *b, param *p )
{
	fields *ref;
	long i;
	char buf[512];
	int n;
	for ( i=0; i<b->nrefs; ++i ) {
		ref = b->ref[i];
		n = fields_find( ref, "REFNUM", 0 );
		if ( n==-1 ) n = build_refnum( ref, i+1 );
		if ( p->addcount ) {
			sprintf( buf, "_%ld", i+1 );
			newstr_strcat( &(ref->data[n]), buf );
		}
	}
}
