lqdecompositionunpacked(ap::real_2d_array a,
     int m,
     int n,
     ap::real_2d_array& l,
     ap::real_2d_array& q)
{
    int i;
    int j;
    ap::real_1d_array tau;

    if( n<=0 )
    {
        return;
    }
    q.setbounds(1, n, 1, n);
    l.setbounds(1, m, 1, n);


    lqdecomposition(a, m, n, tau);


    for(i = 1; i <= m; i++)
    {
        for(j = 1; j <= n; j++)
        {
            if( j>i )
            {
                l(i,j) = 0;
            }
            else
            {
                l(i,j) = a(i,j);
            }
        }
    }


    unpackqfromlq(a, m, n, tau, n, q);
}
