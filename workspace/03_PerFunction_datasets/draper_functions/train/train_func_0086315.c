ScrambleSalt( nSalt & salt, tString const & serverIP ) const
{
    if ( method != "bmd5" )
    {

        nSalt tmp;
        nKrawall::ScramblePassword( serverIP, tmp );
        nKrawall::ScrambleWithSalt2( salt, tmp, salt );
    }
}
