PopSeqStat (
    UInt                nr )
{
    Stat                body;
    Stat                stat;
    UInt                i;

    if (nr == 0 ) {
      body = NewStat(T_EMPTY, 0);
    }

    else if ( nr == 1 ) {
        body = PopStat();
    }


    else {


        if ( 2 <= nr && nr <= 7 ) {
            body = NewStat( T_SEQ_STAT+(nr-1), nr * sizeof(Stat) );
        }
        else {
            body = NewStat( T_SEQ_STAT,        nr * sizeof(Stat) );
        }


        for ( i = nr; 1 <= i; i-- ) {
            stat = PopStat();
            ADDR_STAT(body)[i-1] = stat;
        }
    }


    return body;
}
