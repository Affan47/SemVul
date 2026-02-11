generate_citekey( fields *info, int nref )
{
	newstr citekey;
	int n1, n2;
	char *p, buf[100];
	newstr_init( &citekey );
	n1 = fields_find( info, "AUTHOR", 0 );
	if ( n1==-1 ) n1 = fields_find( info, "AUTHOR", -1 );
	n2 = fields_find( info, "YEAR", 0 );
	if ( n2==-1 ) n2 = fields_find( info, "YEAR", -1 );
	if ( n2==-1 ) n2 = fields_find( info, "PARTYEAR", 0 );
	if ( n2==-1 ) n2 = fields_find( info, "PARTYEAR", -1 );
	if ( n1!=-1 && n2!=-1 ) {
		p = info->data[n1].data;
		while ( p && *p && *p!='|' ) {
			if ( !is_ws( *p ) ) newstr_addchar( &citekey, *p );
			p++;
		}
		p = info->data[n2].data;
		while ( p && *p ) {
			if ( !is_ws( *p ) ) newstr_addchar( &citekey, *p );
			p++;
		}
		fields_add( info, "REFNUM", citekey.data, 0 );
	} else {
		sprintf( buf, "ref%d\n", nref );
		newstr_strcpy( &citekey, buf );
	}
	newstr_free( &citekey );
	return fields_find( info, "REFNUM", -1 );
}
