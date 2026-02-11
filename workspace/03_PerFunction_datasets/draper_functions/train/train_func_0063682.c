SlurpFont(Face *face) {
    FILE *bdffile = fopen(face->filename,"r");
    struct bdffont *bdffont;
    char buffer[MAX_WIDTH+1];
    char **chr;
    int i, enc, last_enc= -1;

    if ( bdffile==NULL ) {
	fprintf( stderr, "Can't open %s\n", face->filename );
return( NULL );
    }
    bdffont = calloc(1,sizeof(*bdffont));
    bdffont->face = face;

    fgets(buffer,sizeof(buffer),bdffile);
    bdffont->header = SlurpChar(bdffile,buffer, sizeof(buffer), "ENDPROPERTIES", &enc);
    fgets(buffer,sizeof(buffer),bdffile);

    fgets(buffer,sizeof(buffer),bdffile);
    while ( strcmp(buffer,"ENDFONT\n")!=0 ) {
	chr = SlurpChar(bdffile,buffer, sizeof(buffer), "ENDCHAR", &enc);
	if ( enc!=-1 ) {
	    if ( enc>=bdffont->charmax ) {
		int new = enc+256;
		if ( bdffont->charmax==0 ) bdffont->chars = malloc(new*sizeof(char **));
		else bdffont->chars = realloc(bdffont->chars,new*sizeof(char **));
		for ( i=bdffont->charmax; i<new; ++i )
		    bdffont->chars[i] = NULL;
		bdffont->charmax = new;
	    }
	    bdffont->chars[enc] = chr;
	    last_enc = enc;
	}
	if ( fgets(buffer,sizeof(buffer),bdffile)==NULL )
    break;
    }
return( bdffont );
}
