ReadDir( tCommandLineParser & parser, tString & target, const char* argument )
{
    if ( parser.GetOption( target, argument ) )
    {
        target = expand_home_c( target );

        return true;
    }

    return false;
}
