output_title( fields *info, FILE *outptr, int level )
{
	int ttl = fields_find( info, "TITLE", level );
	int subttl = fields_find( info, "SUBTITLE", level );
	int shrttl = fields_find( info, "SHORTTITLE", level );

	output_tab1( outptr, level, "<titleInfo>\n" );
	output_fill2( outptr, increment_level(level,1), "title", info, ttl, 1);
	output_fill2( outptr, increment_level(level,1), "subTitle", info, subttl, 1 );
	if ( ttl==-1 && subttl==-1 )
		output_tab1( outptr, increment_level(level,1), "<title/>\n" );
	output_tab1( outptr, level, "</titleInfo>\n" );


	if ( shrttl!=-1 ) {
		if ( ttl==-1 || subttl!=-1 ||
			strcmp(info->data[ttl].data,info->data[shrttl].data) ) {
			output_tab1( outptr, level,
					"<titleInfo type=\"abbreviated\">\n" );
			output_fill2( outptr, level+1, "title", info, shrttl,1);
			output_tab1( outptr, level, "</titleInfo>\n" );
		}
		fields_setused( info, shrttl );
	}
}
