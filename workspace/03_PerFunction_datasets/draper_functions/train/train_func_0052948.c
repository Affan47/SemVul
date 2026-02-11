loadString(FILE *file, struct gcontext *gc) {
    int i, ch;

    ch = getc(file);
    if ( ch!='"' ) {
	ungetc(ch,file);
return( NULL );
    }
    for ( i=0 ; (ch=getc(file))!=EOF && ch!='"' ; ++i ) {
	if ( i+1>=gc->bmax ) {
	    gc->bmax += 100;
	    gc->buffer = grealloc(gc->buffer,gc->bmax);
	}
	gc->buffer[i] = ch;
    }
    if ( ch==EOF )
return( NULL );

    if ( i==0 )
return( copy(""));
    gc->buffer[i] = '\0';
return( copy( gc->buffer ));
}
