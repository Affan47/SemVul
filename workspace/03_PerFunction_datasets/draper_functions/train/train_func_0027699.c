elm_5node_pyramid_fvalue(double *F,double u,double v,double w)
{
     double R=0.0, s;
     int i;

     if ( w == 1 ) w = 1-1.0e-12;
     s = 1.0 / (1-w);

     R = R + F[0] * ( (1-u) * (1-v) - w + u*v*w * s ) / 4;
     R = R + F[1] * ( (1+u) * (1-v) - w - u*v*w * s ) / 4;
     R = R + F[2] * ( (1+u) * (1+v) - w + u*v*w * s ) / 4;
     R = R + F[3] * ( (1-u) * (1+v) - w - u*v*w * s ) / 4;
     R = R + F[4] * w;

     return R;
}
