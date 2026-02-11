output_people( FILE *fp, fields *info, char *tag, char *isitag, int level )
{
	int n = 0, i;
        for ( i=0; i<info->nfields; ++i ) {
                if ( strcasecmp( info->tag[i].data, tag ) ) continue;
		if ( level!=-1 && info->level[i]!=level ) continue;
		if ( n==0 ) {
			fprintf( fp, "%s ", isitag );
		} else {
			fprintf( fp, "   " );
		}
		output_person( fp, info->data[i].data );
		fprintf( fp, "\n" );
		n++;
	}
}
