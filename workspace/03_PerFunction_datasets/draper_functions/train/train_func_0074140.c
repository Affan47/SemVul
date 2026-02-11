DeAllocateBnData( BN_DATA *pBD )
{
    if ( pBD ) {
        if ( pBD->BasePtr )
            inchi_free( pBD->BasePtr );
        if ( pBD->SwitchEdge )
            inchi_free( pBD->SwitchEdge );
        if ( pBD->Tree )
            inchi_free( pBD->Tree );
        if ( pBD->ScanQ )
            inchi_free( pBD->ScanQ );
        if ( pBD->Pu )
            inchi_free( pBD->Pu );
        if ( pBD->Pv )
            inchi_free( pBD->Pv );
#if( BNS_RAD_SEARCH == 1 )
        if ( pBD->RadEndpoints ) {
            inchi_free( pBD->RadEndpoints );
        }
        if ( pBD->RadEdges ) {
            inchi_free( pBD->RadEdges );
        }
#endif
        inchi_free( pBD );
    }
    return NULL;
}
