endxmlin_datar( xml *node, newstr *s )
{
	if ( node->value && node->value->len )
		newstr_strcat( s, node->value->data );
	if ( node->down && xml_tagexact( node->down, "style" ) )
		endxmlin_datar( node->down, s );
	if ( xml_tagexact( node, "style" ) && node->next )
		endxmlin_datar( node->next, s );
}
