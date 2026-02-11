elm_6node_wedge_fvalue(double *F,double u,double v,double w)
{
     double R=0.0,uw=u*w,vw=v*w;
     int i;

     for( i=0; i<6; i++ )
     {
         R += F[i]*(N[i][0]+
                    N[i][1]*u+
                    N[i][2]*v+
                    N[i][3]*w+
                    N[i][4]*uw+
                    N[i][5]*vw);
     }

     return R;
}
