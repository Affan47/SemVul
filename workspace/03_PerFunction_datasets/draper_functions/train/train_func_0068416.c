print_resid (int ok, cs_ci *A, cs_complex_t *x, cs_complex_t *b, cs_complex_t *resid)
{
    int i, m, n ;
    if (!ok) { printf ("    (failed)\n") ; return ; }
    m = A->m ; n = A->n ;
    for (i = 0 ; i < m ; i++) resid [i] = -b [i] ;
    cs_ci_gaxpy (A, x, resid) ;
    printf ("resid: %8.2e\n", norm (resid,m) / ((n == 0) ? 1 :
        (cs_ci_norm (A) * norm (x,n) + norm (b,m)))) ;
}
