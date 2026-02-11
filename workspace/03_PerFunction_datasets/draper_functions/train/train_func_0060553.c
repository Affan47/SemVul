n2n_tick_transop( n2n_edge_t * eee, time_t now )
{
    n2n_tostat_t tst;
    size_t trop = eee->tx_transop_idx;


    tst = (eee->transop[N2N_TRANSOP_NULL_IDX].tick)( &(eee->transop[N2N_TRANSOP_NULL_IDX]), now );
    tst = (eee->transop[N2N_TRANSOP_AESCBC_IDX].tick)( &(eee->transop[N2N_TRANSOP_AESCBC_IDX]), now );
    if ( tst.can_tx )
    {
        traceEvent( TRACE_DEBUG, "can_tx AESCBC (idx=%u)", (unsigned int)N2N_TRANSOP_AESCBC_IDX );
        trop = N2N_TRANSOP_AESCBC_IDX;
    }

    tst = (eee->transop[N2N_TRANSOP_TF_IDX].tick)( &(eee->transop[N2N_TRANSOP_TF_IDX]), now );
    if ( tst.can_tx )
    {
        traceEvent( TRACE_DEBUG, "can_tx TF (idx=%u)", (unsigned int)N2N_TRANSOP_TF_IDX );
        trop = N2N_TRANSOP_TF_IDX;
    }

    if ( trop != eee->tx_transop_idx )
    {
        eee->tx_transop_idx = trop;
        traceEvent( TRACE_NORMAL, "Chose new tx_transop_idx=%u", (unsigned int)(eee->tx_transop_idx) );
    }

    return 0;
}
