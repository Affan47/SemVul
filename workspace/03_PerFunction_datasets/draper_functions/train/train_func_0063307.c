output_simpleall( FILE *fp, fields *info, char *intag, char *outtag,
		int format_opts )
{
	int i;
	for ( i=0; i<info->nfields; ++i ) {
		if ( strcasecmp( info->tag[i].data, intag ) ) continue;
		output_and_use( fp, info, i, outtag, format_opts );
	}
}
