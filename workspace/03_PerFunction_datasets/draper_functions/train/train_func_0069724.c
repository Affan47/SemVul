SkipWhite()

{
    for( ; TRUE; )
    {

        if( isspace( (unsigned char)*pszHeaderNext ) )
        {
            pszHeaderNext++;
            continue;
        }


        if( *pszHeaderNext == '/' && pszHeaderNext[1] == '*' )
        {
            pszHeaderNext += 2;

            while( *pszHeaderNext != '\0'
                   && (*pszHeaderNext != '*'
                       || pszHeaderNext[1] != '/' ) )
            {
                pszHeaderNext++;
            }

            pszHeaderNext += 2;
            continue;
        }


        if( *pszHeaderNext == '#'  )
        {
            pszHeaderNext += 1;


            while( *pszHeaderNext != '\0'
                   && *pszHeaderNext != 10
                   && *pszHeaderNext != 13 )
            {
                pszHeaderNext++;
            }
            continue;
        }


        return;
    }
}
