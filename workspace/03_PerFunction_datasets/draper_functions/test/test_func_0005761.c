IsLegalPlayerName( tString const & name )
{

    tString stripped( tColoredString::RemoveColors( name ) );


    for ( int i = stripped.Len()-2; i>=0; --i )
    {
        if ( !isblank( stripped(i) ) )
            return true;
    }

    return false;
}
