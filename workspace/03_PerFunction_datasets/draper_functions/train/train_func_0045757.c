SetDoubleAttribute( const std::string& name, double val )
{
	TiXmlAttribute* attrib = attributeSet.FindOrCreate( name );
	if ( attrib ) {
		attrib->SetDoubleValue( val );
	}
}
