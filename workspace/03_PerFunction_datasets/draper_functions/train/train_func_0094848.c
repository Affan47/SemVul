calcls (
    struct Control_Points *cp,
    struct MATRIX *m,
    double a[],
    double b[],
    double E[],
    double N[]
)
{
    int i, j, n, numactive = 0;


    for(i = 1 ; i <= m->n ; i++)
    {
        for(j = i ; j <= m->n ; j++)
            M(i,j) = 0.0;
        a[i-1] = b[i-1] = 0.0;
    }


    for(n = 0 ; n < cp->count ; n++)
    {
        if(cp->status[n] > 0)
        {
            numactive++;
            for(i = 1 ; i <= m->n ; i++)
            {
                for(j = i ; j <= m->n ; j++)
                    M(i,j) += term(i,cp->e1[n],cp->n1[n]) * term(j,cp->e1[n],cp->n1[n]);

                a[i-1] += cp->e2[n] * term(i,cp->e1[n],cp->n1[n]);
                b[i-1] += cp->n2[n] * term(i,cp->e1[n],cp->n1[n]);
            }
        }
    }

    if(numactive <= m->n)
        return(MINTERR);


    for(i = 2 ; i <= m->n ; i++)
    {
        for(j = 1 ; j < i ; j++)
            M(i,j) = M(j,i);
    }

    return(solvemat(m,a,b,E,N));
}
