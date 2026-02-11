endxmlin_contributor( xml *node, fields *info, char *int_tag, int level )
{
	endxmlin_data( node, int_tag, info, level );
	if ( node->next )
		endxmlin_contributor( node->next, info, int_tag, level );
}
