elm_5node_quad_dndu_fvalue( double *F, double u, double v )
{
     double R=0.0,uv=u*v,vv=v*v;
     int i;

     for( i=0; i<5; i++ )
     {
         R += F[i]*(N[i][1]+N[i][3]*v+2*N[i][4]*u*v*v );
     }

     return R;
}
