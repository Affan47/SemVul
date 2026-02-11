gifti_strdup( const char * src )
{
    char * newstr;
    int    len;

    if( !src ) return NULL;

    len = strlen(src) + 1;

    newstr = (char *)malloc(len * sizeof(char));
    if( !newstr ) {
        fprintf(stderr,"** failed gifti_strdup, len = %d\n", len);
        return NULL;
    }

    strcpy(newstr, src);

    return newstr;
}
