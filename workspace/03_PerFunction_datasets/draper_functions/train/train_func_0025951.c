elm_4node_quad_isoline
  (
     double K, double *F, double *C,double *X,double *Y,double *Z,line_t *Line
  )
{
    double f[3],c[3],x[3],y[3],z[3];

    int i, n=0, above=0;

    for( i=0; i<4; i++ ) above += F[i]>K;
    if ( above == 0 || above == 4 ) return 0;

    f[0] = elm_4node_quad_fvalue( F,0.0,0.0 );
    c[0] = elm_4node_quad_fvalue( C,0.0,0.0 );
    x[0] = elm_4node_quad_fvalue( X,0.0,0.0 );
    y[0] = elm_4node_quad_fvalue( Y,0.0,0.0 );
    z[0] = elm_4node_quad_fvalue( Z,0.0,0.0 );

    f[1] = F[3];
    c[1] = C[3];
    x[1] = X[3];
    y[1] = Y[3];
    z[1] = Z[3];
    for( i=0; i<4; i++ )
    {
        f[2] = F[i];
        c[2] = C[i];
        x[2] = X[i];
        y[2] = Y[i];
        z[2] = Z[i];

        n += elm_3node_triangle_isoline( K,f,c,x,y,z,&Line[n] );

        f[1] = F[i];
        c[1] = C[i];
        x[1] = X[i];
        y[1] = Y[i];
        z[1] = Z[i];
    }

    return n;
}
