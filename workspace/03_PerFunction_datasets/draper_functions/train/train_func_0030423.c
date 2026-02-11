check_n_input( const char *str )
{
    unsigned i;
    char c;

    for ( i = 0; i < strlen(str); i++)
    {
        c = str[i];
        if ( i==0 )
        {
            if ( c < 49 || c > 57  )
                return -1;
        }
        else
            if ( c < 48 || c > 57  )
                return -1;
    }
    return 1;
}
