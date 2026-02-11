output_line_collection(uchar* geom,outfunc func,int supress)
{
	int cnt = read_int(&geom);
	int orig_cnt = cnt;

	if ( cnt == 0 ){
		write_str(" EMPTY");
	}
	else{
		write_str("(");
		while(cnt--){
			geom=func(geom,supress);
			if ( cnt ){
				write_str(",");
			}
		}
		write_str(")");
	}


	if ((current_unparser_check_flags & PARSER_CHECK_MINPOINTS) && orig_cnt < 2)
		LWGEOM_WKT_UNPARSER_ERROR(UNPARSER_ERROR_MOREPOINTS);

	return geom;
}
