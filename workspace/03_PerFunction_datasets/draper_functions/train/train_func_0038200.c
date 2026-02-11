elm_27node_brick_dndu_fvalue(double *F,double u,double v,double w)
{
     double R=0.0,vw=v*w,u2=2*u,u2v=u2*v,u2w=u2*w,vv=v*v,ww=w*w,u2vw=u2*vw,vvw=vv*w,vww=v*ww;
     int i;

     for( i=0; i<27; i++ )
     {
         R += F[i]*( N[i][1]       +
                     N[i][4]*v     +
                     N[i][5]*w     +
                     N[i][7]*vw    +
                     N[i][8]*u2    +
                     N[i][11]*u2v  +
                     N[i][12]*u2w  +
                     N[i][13]*vv   +
                     N[i][14]*ww   +
                     N[i][17]*u2vw +
                     N[i][18]*vvw  +
                     N[i][19]*vww  +
                     N[i][20]*2*u*v*v +
                     N[i][21]*2*u*w*w +
                     N[i][23]*v*v*w*w +
                     N[i][24]*2*u*v*w*w +
                     N[i][25]*2*u*v*v*w +
                     N[i][26]*2*u*v*v*w*w );
     }

     return R;
}
