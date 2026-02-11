medin_pubmedarticle( xml *node, fields *info )
{
	if ( node->down ) {
		if ( xml_tagexact( node, "MedlineCitation" ) )
			medin_medlinecitation( node->down, info );
		else if ( xml_tagexact( node, "PubmedData" ) )
			medin_pubmeddata( node->down, info );
	}
	if ( node->next ) medin_pubmedarticle( node->next, info );
}
