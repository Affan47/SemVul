isWon()
{

    for (int o = 0; o < 8; ++o)
    {
        if ( ( Wlen[outs + o] == 0 ) || ( RANK( *Wp[outs + o] ) != PS_KING ) )
            return false;
    }

    return true;
}
