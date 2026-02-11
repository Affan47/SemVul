cs_randperm (csi n, csi seed)
{
    csi *p, k, j, t ;
    if (seed == 0) return (NULL) ;
    p = cs_malloc (n, sizeof (csi)) ;
    if (!p) return (NULL) ;
    for (k = 0 ; k < n ; k++) p [k] = n-k-1 ;
    if (seed == -1) return (p) ;
    srand (seed) ;
    for (k = 0 ; k < n ; k++)
    {
        j = k + (rand ( ) % (n-k)) ;
        t = p [j] ;
        p [j] = p [k] ;
        p [k] = t ;
    }
    return (p) ;
}
