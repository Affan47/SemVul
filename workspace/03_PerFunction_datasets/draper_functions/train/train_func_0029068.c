output_type( FILE *fp, int type, int format_opts )
{
	typedef struct {
		int bib_type;
		char *type_name;
	} typenames;

	typenames types[] = {
		{ TYPE_ARTICLE, "Article" },
		{ TYPE_INBOOK, "Inbook" },
		{ TYPE_PROCEEDINGS, "Proceedings" },
		{ TYPE_INPROCEEDINGS, "InProceedings" },
		{ TYPE_BOOK, "Book" },
		{ TYPE_PHDTHESIS, "PhdThesis" },
		{ TYPE_MASTERSTHESIS, "MastersThesis" },
		{ TYPE_REPORT, "TechReport" },
		{ TYPE_MANUAL, "Manual" },
		{ TYPE_COLLECTION, "Collection" },
		{ TYPE_INCOLLECTION, "InCollection" },
		{ TYPE_UNPUBLISHED, "Unpublished" },
		{ TYPE_ELECTRONIC, "Electronic" },
		{ TYPE_MISC, "Misc" } };
	int i, len, ntypes = sizeof( types ) / sizeof( types[0] );
	char *s = NULL;
	for ( i=0; i<ntypes; ++i ) {
		if ( types[i].bib_type == type ) {
			s = types[i].type_name;
			break;
		}
	}
	if ( !s ) s = types[ntypes-1].type_name;
	if ( !(format_opts & BIBOUT_UPPERCASE ) ) fprintf( fp, "@%s{", s );
	else {
		len = strlen( s );
		fprintf( fp, "@" );
		for ( i=0; i<len; ++i )
			fprintf( fp, "%c", toupper(s[i]) );
		fprintf( fp, "{" );
	}
}
