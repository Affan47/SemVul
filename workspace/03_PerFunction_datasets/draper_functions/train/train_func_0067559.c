RemoveAttribute( const char * name )
{
	TIXML_STRING str( name );
	TiXmlAttribute* node = attributeSet.Find( str );
	if ( node )
	{
		attributeSet.Remove( node );
		delete node;
	}
}
