cs_symperm (const cs *A, const int *pinv, int values)
{
    int i, j, p, q, i2, j2, n, *Ap, *Ai, *Cp, *Ci, *w ;
    double *Cx, *Ax ;
    cs *C ;
    if (!CS_CSC (A)) return (NULL) ;
    n = A->n ; Ap = A->p ; Ai = A->i ; Ax = A->x ;
    C = cs_spalloc (n, n, Ap [n], values && (Ax != NULL), 0) ;
    w = cs_calloc (n, sizeof (int)) ;
    if (!C || !w) return (cs_done (C, w, NULL, 0)) ;
    Cp = C->p ; Ci = C->i ; Cx = C->x ;
    for (j = 0 ; j < n ; j++)
    {
        j2 = pinv ? pinv [j] : j ;
        for (p = Ap [j] ; p < Ap [j+1] ; p++)
        {
            i = Ai [p] ;
            if (i > j) continue ;
            i2 = pinv ? pinv [i] : i ;
            w [CS_MAX (i2, j2)]++ ;
        }
    }
    cs_cumsum (Cp, w, n) ;
    for (j = 0 ; j < n ; j++)
    {
        j2 = pinv ? pinv [j] : j ;
        for (p = Ap [j] ; p < Ap [j+1] ; p++)
        {
            i = Ai [p] ;
            if (i > j) continue ;
            i2 = pinv ? pinv [i] : i ;
            Ci [q = w [CS_MAX (i2, j2)]++] = CS_MIN (i2, j2) ;
            if (Cx) Cx [q] = Ax [p] ;
        }
    }
    return (cs_done (C, w, NULL, 1)) ;
}
