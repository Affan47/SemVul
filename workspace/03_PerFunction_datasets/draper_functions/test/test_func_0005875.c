output_easy( FILE *fp, fields *info, long refnum, char *tag, char *ristag, int level )
{
	int n = fields_find( info, tag, level );
	if ( n!=-1 ) {
		fprintf( fp, "%s  - %s\n", ristag, info->data[n].data );
	}
}
