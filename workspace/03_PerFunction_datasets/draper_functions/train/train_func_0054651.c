utf82u_copy(const char *utf8buf) {
    int len;
    unichar_t *ubuf;

    if ( utf8buf==NULL )
return( NULL );

    len = strlen(utf8buf);
    ubuf = galloc((len+1)*sizeof(unichar_t));
return( utf82u_strncpy(ubuf,utf8buf,len+1));
}
