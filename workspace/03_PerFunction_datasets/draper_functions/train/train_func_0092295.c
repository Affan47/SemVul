_signature( SV * sv, HV * seen, AV * infos ) {
    I32 i;
    U32 len;
    SV **AValue;
    HV *myHash;
    HE *HEntry;
    char *HKey;

  testvar1:

    if ( SvROK( sv ) ) {
        if ( has_seen( sv, seen ) )
            return infos;

        av_push( infos, _get_infos( sv ) );
        sv = SvRV( sv );
        goto testvar1;

    }
    else {

        av_push( infos, _get_infos( sv ) );
        switch ( SvTYPE( sv ) ) {
        case SVt_PVAV:
            for ( i = 0; i <= av_len( ( AV * ) sv ); i++ ) {
                AValue = av_fetch( ( AV * ) sv, i, 0 );
                if ( AValue )
                    _signature( *AValue, seen, infos );
            }
            break;

        case SVt_PVHV:
            myHash = ( HV * ) sv;
            hv_iterinit( myHash );
            while ( HEntry = hv_iternext( myHash ) ) {
                STRLEN len;
                HKey = HePV( HEntry, len );
                _signature( HeVAL( HEntry ), seen, infos );
            }
            break;

        }
    }
    return infos;
}
