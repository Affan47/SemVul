repl_new_lines( char *text )
{
    int i;
    for ( i = 0; i < strlen( text ); i++ )
        if ( text[i] < 32 )
            text[i] = 32;
}
