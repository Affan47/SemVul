uc_strstr(const unichar_t *longer, const char *substr) {
    long ch1, ch2;
    const unichar_t *lpt, *str1; const char *str2;

    for ( lpt=longer; *lpt!='\0'; ++lpt ) {
	str1 = lpt; str2 = substr;
	for (;;) {
	    ch1 = *str1++; ch2 = *(unsigned char *) str2++ ;
	    if ( ch2=='\0' )
return((unichar_t *) lpt);
	    if ( ch1!=ch2 )
	break;
	}
    }
return( NULL );
}
