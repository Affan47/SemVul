bibl_fixcharsets( bibl *b, param *p )
{
	fields *ref;
	long i, j;
	int swap = 0;
	int latexout = p->latexout;
	int latexin  = p->latexin;
	for ( i=0; i<b->nrefs; ++i ) {
		ref = b->ref[i];
		for ( j=0; j<ref->nfields; ++j ) {
			if ( latexin || latexout ) {

				if ( !strcasecmp( ref->tag[j].data, "DOI" ) ||
				     !strcasecmp( ref->tag[j].data, "URL" ) ||
				     !strcasecmp( ref->tag[j].data, "REFNUM" )){
					latexin  = 0;
					latexout = 0;
					swap = 1;
				}
			}
			newstr_convert( &(ref->data[j]),
				p->charsetin,  latexin,  p->utf8in,
				p->xmlin,
				p->charsetout, latexout, p->utf8out,
				p->xmlout );
			if ( swap ) {
				swap = 0;
				latexin  = p->latexin;
				latexout = p->latexout;
			}
		}
	}
}
