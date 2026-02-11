_cleanfilename(char *filename) {
    char *pt, *npt;
    int ch, exists, ch2;

    for ( ch = *(pt=npt=filename); ch!='\0'; ch = *++pt ) {
	if ( ch>'!' && ch!='*' && ch!='?' && ch!='/' && ch!='\\' && ch!='[' && ch<0x7f )
	    *npt++ = ch;
    }
    *npt = '\0';
    if ( force && !inquire )
return( true );

    exists = access(filename,F_OK)==0;

    forever {
	if ( exists )
	    fprintf( stderr, "%s exists, do you want to overwrite it? (n) ", filename );
	else if ( inquire )
	    fprintf( stderr, "Write %s? (y) ", filename );
	else
return( true );
	ch = getchar();
	if ( ch=='q' || ch=='Q' )
exit(0);
	if ( ch=='a' || ch=='A' ) {
	    force = true;
	    inquire = false;
return( true );
	}
	if ( ch=='y' || ch=='Y' || ch=='n' || ch=='N' || ch==EOF || ch=='\n' ) {
	    if ( ch=='\n' || ch==EOF )
		ch = exists ? 'n' : 'y';
	    else
		while ( (ch2=getchar())!='\n' && ch2!=EOF );
return( ch=='y' || ch=='Y' );
	} else if ( ch=='=' ) {
	    for ( pt=filename; (ch=getchar())!=EOF && ch!='\n'; )
		*pt++ = ch;
return( true );
	} else {
	    fprintf( stderr, "Please answer with 'y'(es), 'n'(o), 'q'(uit), 'a'(ll), or '=new-filename'.\n" );
	}
    }
}
