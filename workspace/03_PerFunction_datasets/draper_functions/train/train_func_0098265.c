cs_bfs (const cs *A, int n, int *wi, int *wj, int *queue,
    const int *imatch, const int *jmatch, int mark)
{
    int *Ap, *Ai, head = 0, tail = 0, j, i, p, j2 ;
    cs *C ;
    for (j = 0 ; j < n ; j++)
    {
        if (imatch [j] >= 0) continue ;
        wj [j] = 0 ;
        queue [tail++] = j ;
    }
    if (tail == 0) return (1) ;
    C = (mark == 1) ? ((cs *) A) : cs_transpose (A, 0) ;
    if (!C) return (0) ;
    Ap = C->p ; Ai = C->i ;
    while (head < tail)
    {
        j = queue [head++] ;
        for (p = Ap [j] ; p < Ap [j+1] ; p++)
        {
            i = Ai [p] ;
            if (wi [i] >= 0) continue ;
            wi [i] = mark ;
            j2 = jmatch [i] ;
            if (wj [j2] >= 0) continue ;
            wj [j2] = mark ;
            queue [tail++] = j2 ;
        }
    }
    if (mark != 1) cs_spfree (C) ;
    return (1) ;
}
