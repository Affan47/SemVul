utf8_2_latin1_copy(const char *utf8buf) {
    int len;
    int ch;
    char *lbuf, *pt; const char *upt;

    if ( utf8buf==NULL )
return( NULL );

    len = strlen(utf8buf);
    pt = lbuf = galloc(len+1);
    for ( upt=utf8buf; (ch=utf8_ildb(&upt))!='\0'; )
	if ( ch>=0xff )
	    *pt++ = '?';
	else
	    *pt++ = ch;
    *pt = '\0';
return( lbuf );
}
