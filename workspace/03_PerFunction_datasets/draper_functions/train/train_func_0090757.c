beautify ( byte * str )
{
   static byte result[ 80 ];
   byte ville[50], code[6];
   byte *r = ville;

   *str = ToUpper ( *str );

    if( ! strchr( str, '\t') )
    {
 	strcpy( result, str );
 	return result ;
    }


    while( *str )
    {
	if( *str == '\t' )
	{
		*r = '\0';
		strcpy( code, str +1 );
		break ;
	}
	*r++ = *str++ ;
	if( *(str -1 ) == ' '|| *(str -1 ) == 39 )
		*str = ToUpper ( *str );
    }

    sprintf(result, "%-30s %s", ville, code );

    return result ;
}
