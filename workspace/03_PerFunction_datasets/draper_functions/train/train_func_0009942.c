medin_article( xml *node, fields *info )
{
	if ( xml_tagexact( node, "Journal" ) )
		medin_journal1( node, info );
	else if ( xml_tagexact( node, "ArticleTitle" ) )
		medin_articletitle( node, info );
	else if ( xml_tagexact( node, "Pagination" ) && node->down )
		medin_pagination( node->down, info );
	else if ( xml_tagexact( node, "Abstract" ) && node->down )
		medin_abstract( node->down, info );
	else if ( xml_tagexact( node, "AuthorList" ) )
		medin_authorlist( node, info );
	else if ( xml_tagexact( node, "Affiliation" ) )
		fields_add( info, "ADDRESS", xml_data( node ), 0 );
	if ( node->next ) medin_article( node->next, info );
}
