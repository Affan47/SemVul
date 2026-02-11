wordin_person( xml *node, fields *info, char *type )
{
	xml *last, *first;
	newstr name;

	newstr_init( &name );

	last = node;
	while ( last && !xml_tagexact( last, "b:Last" ) )
		last = last->next;
	if ( last ) newstr_strcpy( &name, last->value->data );

	first = node;
	while ( first ) {
		if ( xml_tagexact( first, "b:First" ) ) {
			if ( name.len ) newstr_addchar( &name, '|' );
			newstr_strcat( &name, first->value->data );
		}
		first = first->next;
	}

	fields_add( info, type, name.data, 0 );

	newstr_free( &name );
}
