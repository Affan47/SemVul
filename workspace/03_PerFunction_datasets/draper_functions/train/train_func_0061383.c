gnc_sx_incr_temporal_state(const SchedXaction *sx, SXTmpStateData *stateData )
{
    GDate unused;
    SXTmpStateData *tsd = (SXTmpStateData*)stateData;

    g_date_clear( &unused, 1 );
    tsd->last_date =
        xaccSchedXactionGetInstanceAfter( sx,
                                          &unused,
                                          stateData );
    if ( xaccSchedXactionHasOccurDef( sx ) )
    {
        tsd->num_occur_rem -= 1;
    }
    tsd->num_inst += 1;
}
