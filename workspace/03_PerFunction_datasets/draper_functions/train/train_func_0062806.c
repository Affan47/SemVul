strip_newline_from_dir( char *str, int size )
{
    int i;


    for (  i = 0; i < size; ++i )
    {
        if ( str[i] == '\n' )
        {
            str[i] = '\0';


            return;
        }
    }

}
