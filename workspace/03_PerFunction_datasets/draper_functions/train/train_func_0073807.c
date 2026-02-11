elm_5node_quad_fvalue( double *F, double u, double v )
{
     double R,uv=u*v,uu=u*u,vv=v*v,uuv=uu*v,uvv=u*vv;
     int i;

     R = 0.0;
     for( i=0; i<5; i++ )
     {
          R += F[i]*(N[i][0]      +
                     N[i][1]*u    +
                     N[i][2]*v    +
                     N[i][3]*uv   +
                     N[i][4]*uu*vv );
     }

     return R;
}
