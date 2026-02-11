readLine(
  FILE * fp)
{
    int  c;
    char *pbuffer;

    pbuffer = buffer;


    for(;;) {
	c = getc(fp);
	if ( c == EOF) return(NULL);
	if ( c == '\n') {
	    *pbuffer = '\0';
	    return(buffer);
	}
	if ( c != ' ') break;
    }
    do {
	if ( c == '\\' ) {
	    do {
		c = getc(fp);
		if ( c == '\n' ) break;
	    } while ( c != EOF);
	    if ( c != EOF) {
		*pbuffer = ' ';
		pbuffer++;
	    } else return( buffer);
	    c = getc(fp);
	    continue;
	}
	*pbuffer = (char) c;
	pbuffer++;
	c = getc(fp);
    } while( c != '\n' &&  c != EOF);
    *pbuffer = '\0';
    return(buffer);

}
