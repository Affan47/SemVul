modsin_locationr( xml *node, fields *info, int level )
{
	char url[]="URL", school[]="SCHOOL", loc[]="LOCATION";
	char fileattach[]="FILEATTACH", *tag=NULL;

	if ( xml_tag_attrib( node, "url", "access", "raw object" ) ) {
		tag = fileattach;
	} else if ( xml_tagexact( node, "url" ) ) {
		tag = url;
	}

	if ( xml_tag_attrib( node, "physicalLocation", "type", "school" ) ) {
		tag = school;
	} else if ( xml_tagexact( node, "physicalLocation" ) ) {
		tag = loc;
	}

	if ( tag ) fields_add( info, tag, node->value->data, level );

	if ( node->down ) modsin_locationr( node->down, info, level );
	if ( node->next ) modsin_locationr( node->next, info, level );
}
