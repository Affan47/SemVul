_dxf_ImageInfoFromFileName ( char *basename)
{
    int  i;
    char *ep;
    int matches = 0;
    ImageInfo *r = NULL;


    ep = NULL;
    for ( i = strlen ( basename ) - 1;
          i >= 0;
          i-- )
        if ( basename[i] == '.' )
        {
            ep = &basename[i+1];
            break;
        }
        else if ( basename[i] == '/' )
            break;


    if ( ep ) {
        for ( i=0 ; ImageTable[i].type != img_typ_illegal ; i++ ) {
	    int tmp = SearchStringList(ImageTable[i].extensions,ep);
	    if (tmp > matches) {
		r = &ImageTable[i];
		matches = tmp;
	    }
	}
    }
    return r;
}
