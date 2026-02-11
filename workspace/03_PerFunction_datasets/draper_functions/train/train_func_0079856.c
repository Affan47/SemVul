_unbless( SV * sv, HV * seen ) {
    I32 i, len;
    SV **AValue;
    HV *myHash;
    HE *HEntry;

  redo_unbless:
    if ( SvROK( sv ) ) {

        if ( has_seen( sv, seen ) )
            return sv;

        if ( sv_isobject( sv ) ) {
            sv = ( SV * ) SvRV( sv );
            SvOBJECT_off( sv );
        }
        else {
            sv = ( SV * ) SvRV( sv );
        }
        goto redo_unbless;
    }

    switch ( SvTYPE( sv ) ) {

    case SVt_PVAV:{
            dsWARN( "an array\n" );
            len = av_len( ( AV * ) sv );
            for ( i = 0; i <= len; i++ ) {
                AValue = av_fetch( ( AV * ) sv, i, 0 );
                if ( AValue )
                    _unbless( *AValue, seen );
            }
            break;
        }
    case SVt_PVHV:{
            dsWARN( "a hash (PVHV)\n" );
            myHash = ( HV * ) sv;
            hv_iterinit( myHash );
            while ( HEntry = hv_iternext( myHash ) ) {
                _unbless( HeVAL( HEntry ), seen );
            }
            break;
        }
    }
    return sv;
}
