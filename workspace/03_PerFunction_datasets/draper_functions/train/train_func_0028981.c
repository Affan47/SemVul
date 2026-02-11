cs_qrsol (int order, const cs *A, double *b)
{
    double *x ;
    css *S ;
    csn *N ;
    cs *AT = NULL ;
    int k, m, n, ok ;
    if (!CS_CSC (A) || !b) return (0) ;
    n = A->n ;
    m = A->m ;
    if (m >= n)
    {
        S = cs_sqr (order, A, 1) ;
        N = cs_qr (A, S) ;
        x = cs_calloc (S ? S->m2 : 1, sizeof (double)) ;
        ok = (S && N && x) ;
        if (ok)
        {
            cs_ipvec (S->pinv, b, x, m) ;
            for (k = 0 ; k < n ; k++)
            {
                cs_happly (N->L, k, N->B [k], x) ;
            }
            cs_usolve (N->U, x) ;
            cs_ipvec (S->q, x, b, n) ;
        }
    }
    else
    {
        AT = cs_transpose (A, 1) ;
        S = cs_sqr (order, AT, 1) ;
        N = cs_qr (AT, S) ;
        x = cs_calloc (S ? S->m2 : 1, sizeof (double)) ;
        ok = (AT && S && N && x) ;
        if (ok)
        {
            cs_pvec (S->q, b, x, m) ;
            cs_utsolve (N->U, x) ;
            for (k = m-1 ; k >= 0 ; k--)
            {
                cs_happly (N->L, k, N->B [k], x) ;
            }
            cs_pvec (S->pinv, x, b, n) ;
        }
    }
    cs_free (x) ;
    cs_sfree (S) ;
    cs_nfree (N) ;
    cs_spfree (AT) ;
    return (ok) ;
}
