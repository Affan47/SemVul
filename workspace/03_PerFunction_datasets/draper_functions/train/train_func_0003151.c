elm_8node_brick_dndv_fvalue(double *F,double u,double v,double w)
{
     double R=0.0,uw=u*w;
     int i;

     for( i=0; i<8; i++ )
     {
         R += F[i]*(N[i][2] + N[i][4]*u + N[i][6]*w + N[i][7]*uw);
     }

     return R;
}
