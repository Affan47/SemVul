FindPathCap( BN_STRUCT* pBNS, Edge *SwitchEdge, Vertex x, Vertex y, int delta )
{


    Vertex w, z, iwz;
    int    cap, delta2;
    static int level;

    if ( level ++ > 50 ) {
#ifdef _DEBUG
        int stop = 1;
#else
    ;
#endif
    }


    w   = SwitchEdge_Vert1(y);
    z   = SwitchEdge_Vert2(y);
    iwz = SwitchEdge_IEdge(y);


    cap = rescap_mark( pBNS, w, z, iwz );

    if ( IS_BNS_ERROR( cap ) ) {
        level --;
        return cap;
    }
    if ( cap < delta ) {
        delta = cap;
    }

    if ( w != x ) {
        delta2 = FindPathCap( pBNS, SwitchEdge, x, w, delta );
        delta = inchi_min( delta2, delta );
    }
    if ( z != y ) {
        delta2 = FindPathCap( pBNS, SwitchEdge, prim(y), prim(z), delta );
        delta = inchi_min( delta2, delta );
    }
    level --;
    return delta;
}
