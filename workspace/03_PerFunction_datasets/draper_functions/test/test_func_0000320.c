cs_l_real (cs_cl *A, cs_long_t real)
{
    cs_dl *C ;
    cs_long_t n, triplet, nn, p, nz, *Ap, *Ai, *Cp, *Ci ;
    cs_complex_t *Ax ;
    double *Cx ;
    if (!A || !A->x) return (NULL) ;
    n = A->n ; Ap = A->p ; Ai = A->i ; Ax = A->x ;
    triplet = (A->nz >= 0) ;
    nz = triplet ? A->nz : Ap [n] ;
    C = cs_dl_spalloc (A->m, n, A->nzmax, 1, triplet) ;
    if (!C) return (NULL) ;
    Cp = C->p ; Ci = C->i ; Cx = C->x ;
    nn = triplet ? nz : (n+1) ;
    for (p = 0 ; p < nz ; p++) Ci [p] = Ai [p] ;
    for (p = 0 ; p < nn ; p++) Cp [p] = Ap [p] ;
    for (p = 0 ; p < nz ; p++) Cx [p] = real ? creal (Ax [p]) : cimag (Ax [p]) ;
    if (triplet) C->nz = nz ;
    return (C) ;
}
