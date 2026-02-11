ebiin_publication( xml *node, fields *info )
{
	if ( node->down ) {
		if ( xml_tagexact( node, "Article" ) )
			ebiin_article( node->down, info );
		else if ( xml_tagexact( node, "Book" ) )
			ebiin_book( node->down, info, 0 );
		else if ( xml_tagexact( node, "Report" ) )
			ebiin_book( node->down, info, 0 );
		else if ( xml_tagexact( node, "JournalInfo" ) )
			ebiin_journal2( node->down, info );
		else if ( xml_tagexact( node, "MeshHeadingList" ) )
			ebiin_meshheadinglist( node->down, info );
	}
	if ( node->next ) ebiin_publication( node->next, info );
}
