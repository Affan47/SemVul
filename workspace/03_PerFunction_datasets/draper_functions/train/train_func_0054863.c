output_fill2( FILE *outptr, int level, char *tag, fields *info, int n, int cr )
{
	if ( n!=-1 ) {
		output_tab2_attrib( outptr, level, tag, info->data[n].data,
			NULL, NULL, cr );
		fields_setused( info, n );
	}
}
