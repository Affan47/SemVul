ortho_hash_function(char *s)
{
unsigned int j = 0;

    if ( use_host_hash <= 0 ) return(0);

    while (*s) {
        j += *(s++);
    }

    return( j );
}
