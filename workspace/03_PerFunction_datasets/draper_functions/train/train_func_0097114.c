ebiin_title( xml *node, fields *info, int title_level )
{
	if ( xml_hasdata( node ) )
		fields_add( info, "TITLE", xml_data( node ), title_level );
}
