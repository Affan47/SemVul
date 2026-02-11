FilterName( tString const & in, tString & out )
{
    int i;
    static ePlayerCharacterFilter filter;
    out = tColoredString::RemoveColors( in );


    for ( i = out.Len()-1; i>=0; --i )
    {
        char & c = out[i];

        c = filter.Filter( c );
    }


    se_StripMatchingEnds( out, se_IsUnderscore, se_IsUnderscore );
}
