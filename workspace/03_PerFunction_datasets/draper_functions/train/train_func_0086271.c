_FindFontName(FState *fonts, char *name) {
    struct font_name *fn;
    int ch;

    ch = *name;
    if ( isupper(ch)) ch = tolower(ch);
    if ( ch<'a' ) ch = 'q'; else if ( ch>'z' ) ch='z';
    ch -= 'a';
    fn = fonts->font_names[ch];
    while ( fn!=NULL ) {
	if ( uc_strmatch(fn->family_name,name)==0 )
return( fn );
	fn = fn->next;
    }
return( NULL );
}
