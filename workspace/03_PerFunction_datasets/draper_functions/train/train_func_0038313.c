ReportLag( REAL lag, REAL weight )
    {
#ifdef DEBUG
        con << "Received message of " << lag << " seconds of lag, weight " << weight << "\n";
#endif


        lag = lag > se_lagCreditSingle ? se_lagCreditSingle : lag;


        if ( weight > 1 )
            lagLast_ = tSysTimeFloat();

        REAL slowWeight = weight * se_lagSlowWeight;
        slowWeight = slowWeight > 1 ? 1 : slowWeight;
        REAL fastWeight = weight * se_lagFastWeight;
        fastWeight = fastWeight > 1 ? 1 : fastWeight;

        lagFast_ = smoothLag_ + lag * fastWeight;
        lagSlow_ = ( smoothLag_ > lagSlow_ ? lagSlow_ : smoothLag_ ) + lag * slowWeight;
    }
