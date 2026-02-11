Print( FILE* cfile, int depth ) const
{
	const TiXmlNode* node;
	for ( node=FirstChild(); node; node=node->NextSibling() )
	{
		node->Print( cfile, depth );
		fprintf( cfile, "\n" );
	}
}
