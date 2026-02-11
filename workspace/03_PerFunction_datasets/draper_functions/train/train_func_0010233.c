get_type( fields *info )
{
	char *tag, *data;
        int type = TYPE_UNKNOWN, i;
        for ( i=0; i<info->nfields; ++i ) {
		tag = info->tag[i].data;
                if ( strcasecmp( tag, "GENRE" ) &&
                     strcasecmp( tag, "NGENRE") ) continue;
		data = info->data[i].data;
                if ( !strcasecmp( data, "periodical" ) ||
                     !strcasecmp( data, "academic journal" ) )
                        type = TYPE_ARTICLE;
                else if ( !strcasecmp( data, "book" ) ) {
                        if ( info->level[i]==0 ) type=TYPE_BOOK;
                        else type=TYPE_INBOOK;
                }
        }
        return type;
}
