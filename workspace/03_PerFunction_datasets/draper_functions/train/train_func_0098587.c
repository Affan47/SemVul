nlPreconditioner_SSOR(NLdouble* x, NLdouble* y) {
    NLdouble omega = nlCurrentContext->omega ;
    static double* work = NULL ;
    static int work_size = 0 ;
    NLuint n = nlCurrentContext->n ;
    if(n != work_size) {
        work = NL_RENEW_ARRAY(NLdouble, work, n) ;
        work_size = n ;
    }

    nlMultLowerInverse(x, work, omega) ;
    nlMultDiagonal(work, omega) ;
    nlMultUpperInverse(work, y, omega) ;

    dscal(n, 2.0 - omega, y, 1) ;
}
