IntrPerm (
    UInt                nrc )
{
    Obj                 perm;
    UInt4 *             ptr4;
    UInt2 *             ptr2;
    UInt                m;
    UInt                k;


    if ( IntrReturning > 0 ) { return; }
    if ( IntrIgnoring  > 0 ) { return; }
    if ( IntrCoding    > 0 ) { CodePerm(nrc); return; }


    if ( nrc == 0 ) {
        perm = NEW_PERM2( 0 );
    }


    else {


        m  = INT_INTOBJ( PopObj() );
        perm = PopObj();


        if ( m <= 65536UL ) {
            ptr2 = ADDR_PERM2( perm );
            ptr4 = ADDR_PERM4( perm );
            for ( k = 1; k <= m; k++ ) {
                ptr2[k-1] = ptr4[k-1];
            };
            RetypeBag( perm, T_PERM2 );
            ResizeBag( perm, m * sizeof(UInt2) );
        }


        else {
            ResizeBag( perm, m * sizeof(UInt4) );
        }

    }


    PushObj( perm );
}
