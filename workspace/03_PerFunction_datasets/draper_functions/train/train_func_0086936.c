ScrambleWithSalt( nScrambleInfo const & info, nScrambledPassword const & scrambled, nSalt const & salt, nScrambledPassword & result ) const
{

    if ( !sn_IsSupportedMethod( method ) )
    {
        memset( &result, 0, sizeof(result) );
        con << tColoredStringProxy(1,0,0) << "INTERNAL ERROR OR PHARMING ATTEMPT:" <<  tColoredStringProxy(1,1,1) << " unsupported hash method " << method << " selected.\n";
        return;
    }


    nKrawall::ScrambleWithSalt2( scrambled, salt, result );
}
