GetPing( void ) const
{


    REAL variance = 1;
    {
        REAL snailVariance = this->snail_.GetDataVariance();
        REAL slowVariance = this->slow_.GetDataVariance();
        REAL fastVariance = this->fast_.GetDataVariance();
        variance = variance < snailVariance ? variance : snailVariance;
        variance = variance < slowVariance ? variance : slowVariance;
        variance = variance < fastVariance ? variance : fastVariance;
    }

    REAL pingSnail  = this->GetPingSnail();
    REAL pingSlow   = this->GetPingSlow();
    REAL pingFast   = this->GetPingFast();


    REAL pingReturn = pingSnail;


    if ( ( pingSlow - pingReturn ) * ( pingSlow - pingReturn ) > variance )
    {

        if ( pingSlow > pingReturn * 2 )
            pingSlow = pingReturn * 2;

        pingReturn = pingSlow;
    }


    if ( ( pingFast - pingReturn ) * ( pingFast - pingReturn ) > variance )
    {
        if ( pingFast > pingReturn * 2 )
            pingFast = pingReturn * 2;

        pingReturn = pingFast;
    }


    return pingReturn + sqrtf(variance) * 1.5;
}
