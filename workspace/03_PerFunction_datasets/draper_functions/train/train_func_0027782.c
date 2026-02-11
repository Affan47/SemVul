_has_circular_ref( SV * sv, HV * parents, HV * seen ) {

    SV *ret;
    SV *found;
    U32 len;
    I32 i;
    SV **AValue;
    HV *myHash;
    HE *HEntry;
    SV **HValue;
#if dsDEBUG
    char errmsg[100];
#endif

    if ( SvROK( sv ) ) {

        char addr[PTRLEN];
        sprintf( addr, "%p", SvRV( sv ) );
        len = strlen( addr );

        if ( hv_exists( parents, addr, len ) ) {
#ifdef SvWEAKREF
            if ( SvWEAKREF( sv ) ) {
                dsWARN( "found a weak reference" );
                return &PL_sv_undef;
            }
            else {
#endif
                dsWARN( "found a circular reference!!!" );
                SvREFCNT_inc( sv );
                return sv;
#ifdef SvWEAKREF
            }
#endif
        }
        if ( hv_exists( seen, addr, len ) ) {
            dsWARN( "circular reference on weak ref" );
            return &PL_sv_undef;
        }

        hv_store( parents, addr, len, NULL, 0 );
        hv_store( seen, addr, len, NULL, 0 );
#ifdef SvWEAKREF
        if ( SvWEAKREF( sv ) ) {
            dsWARN( "found a weak reference 2" );
            ret = _has_circular_ref( SvRV( sv ), newHV(  ), seen );
        }
        else {
#endif
            ret = _has_circular_ref( SvRV( sv ), parents, seen );
#ifdef SvWEAKREF
        }
#endif
        hv_delete( seen, addr, ( U32 ) len, 0 );
        hv_delete( parents, addr, ( U32 ) len, 0 );
        return ret;
    }


    switch ( SvTYPE( sv ) ) {

    case SVt_PVAV:{
            dsWARN( "Array" );
            for ( i = 0; i <= av_len( ( AV * ) sv ); i++ ) {
#if dsDEBUG
                sprintf( errmsg, "next elem %i\n", i );
                warn( errmsg );
#endif
                AValue = av_fetch( ( AV * ) sv, i, 0 );
                if ( AValue ) {
                    found = _has_circular_ref( *AValue, parents, seen );
                    if ( SvOK( found ) )
                        return found;
                }
            }
            break;
        }
    case SVt_PVHV:{
            dsWARN( "Hash" );
            myHash = ( HV * ) sv;
            hv_iterinit( myHash );
            while ( HEntry = hv_iternext( myHash ) ) {
#if dsDEBUG
                STRLEN len2;
                char *HKey = HePV( HEntry, len2 );
                sprintf( errmsg, "NEXT KEY is %s\n", HKey );
                warn( errmsg );
#endif
                found =
                    _has_circular_ref( HeVAL( HEntry ), parents, seen );
                if ( SvOK( found ) )
                    return found;
            }
            break;
        }
    }
    return &PL_sv_undef;
}
