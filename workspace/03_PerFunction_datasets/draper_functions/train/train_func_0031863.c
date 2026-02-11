modsin_title( xml *node, fields *info, int level )
{
	newstr title, subtitle;
	int abbr = xml_tag_attrib( node, "titleInfo", "type", "abbreviated" );
	if ( node->down ) {
		newstrs_init( &title, &subtitle, NULL );
		modsin_titler( node->down, &title, &subtitle );
		if ( title.len ) {
			if ( abbr )
				fields_add( info, "SHORTTITLE", title.data, level );
			else
				fields_add( info, "TITLE", title.data, level );
		}
		if ( subtitle.len ) {
			if ( abbr )
				fields_add( info, "SHORTSUBTITLE", subtitle.data, level );
			else
				fields_add( info, "SUBTITLE", subtitle.data, level );
		}
		newstrs_free( &title, &subtitle, NULL );
	}
}
