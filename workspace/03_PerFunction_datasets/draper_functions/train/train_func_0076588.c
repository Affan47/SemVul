u_strtod(const unichar_t *str, unichar_t **ptr) {
    char buf[60], *pt, *ret;
    const unichar_t *upt;
    double val;
    extern double strtod();

    for ( upt=str, pt=buf; *upt<128 && *upt!='\0' && pt-buf<sizeof(buf)-1; )
	*pt++ = *upt++;
    *pt = '\0';
    val = strtod(buf,&ret);
    if ( ptr!=NULL ) {
	if ( pt==ret )
	    *ptr = (unichar_t *) upt;
	else
	    *ptr = (unichar_t *) (str + (ret-buf));
    }
return( val );
}
