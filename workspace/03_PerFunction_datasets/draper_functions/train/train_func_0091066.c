isiin_processf( fields *isiin, char *p, char *filename, long nref )
{
	newstr tag, data;
	int n;
	newstrs_init( &tag, &data, NULL );
	while ( *p ) {
		newstrs_empty( &tag, &data, NULL );
		p = process_isiline( &tag, &data, p );
		if ( !data.len ) continue;
		if ( (tag.len>1) && isiin_istag( tag.data ) ) {
			fields_add( isiin, tag.data, data.data, 0 );
		} else {
			n = isiin->nfields;
			if ( n>0 ) {

				if ( !strcmp( isiin->tag[n-1].data,"AU") ){
					fields_add( isiin, "AU", data.data, 0);
				} else if ( !strcmp( isiin->tag[n-1].data,"AF") ){
					fields_add( isiin, "AF", data.data, 0);
				}

				else {
					newstr_addchar( &(isiin->data[n-1]),' ');
					newstr_strcat( &(isiin->data[n-1]), data.data );
				}
			}
		}
	}
	newstrs_free( &data, &tag, NULL );
	return 1;
}
