cleanup_wiley_author( fields *endin, int n )
{
	newstr tmp, tmppart;
	int i, nauthor = 0;
	newstrs_init( &tmp, &tmppart, NULL );
	newstr_newstrcpy( &tmp, &( endin->data[n] ) );
	i = 0;
	while ( i<tmp.len ) {
		if ( tmp.data[i]==',' ) {
			if ( nauthor==0 )
				newstr_newstrcpy( &(endin->data[n]), &tmppart );
			else
				fields_add( endin, endin->tag[n].data,
					tmppart.data, endin->level[n] );
			newstr_empty( &tmppart );
			nauthor++;
			while ( i<tmp.len && is_ws( tmp.data[i] ) ) i++;
		} else {
			newstr_addchar( &tmppart, tmp.data[i] );
		}
		i++;
	}
	newstrs_free( &tmp, &tmppart, NULL );
}
