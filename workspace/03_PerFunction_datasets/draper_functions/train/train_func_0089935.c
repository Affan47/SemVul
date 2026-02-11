elm_8node_quad_ddu( double *F,double u,double v,double *Values )
{
    double ddu = 0.0, dudv=0.0, ddv = 0.0;

    int i;

    for( i=0; i<8; i++ )
    {
        ddu  += F[i]*( 2*N[i][4] + 2*v*N[i][6] );
        ddv  += F[i]*( 2*N[i][5] + 2*v*N[i][7] );
        dudv += F[i]*( N[i][3] + 2*u*N[i][6] + 2*v*N[i][7] );
    }

    Values[0] =  ddu;
    Values[1] = dudv;
    Values[2] = dudv;
    Values[3] =  ddv;
}
