Print( FILE* fp, int depth )
{
	int i;
	for ( i=0; i<depth; i++ )
		fprintf( fp, "    " );

	fprintf( fp, "<%s", value.c_str() );

	TiXmlAttribute* attrib;
	for ( attrib = attributeSet.First(); attrib; attrib = attrib->Next() )
	{
		fprintf( fp, " " );
		attrib->Print( fp, 0 );
	}


	TiXmlNode* node;
	if ( firstChild )
	{
		fprintf( fp, ">" );

		for ( node = firstChild; node; node=node->NextSibling() )
		{
	 		if ( !node->ToText() )
				fprintf( fp, "\n" );
			node->Print( fp, depth+1 );
		}
 		fprintf( fp, "\n" );
		for ( i=0; i<depth; i++ )
			fprintf( fp, "    " );
		fprintf( fp, "</%s>", value.c_str() );
	}
	else
	{
		fprintf( fp, " />" );
	}
}
