sinfo_svd_fitting ( float *x,
                   float *y,
                   float *sig,
                   int   ndata,
                   float *a,
                   int   ma,
                   float **u,
                   float **v,
                   float *w,
                   float **cvm,
                   float *chisq,
                   void (*funcs)(float,float *,int) )
{
        int j,i;
        float wmax,tmp,thresh,sum,*b,*afunc;


        b=sinfo_vector(1,ndata);
        afunc=sinfo_vector(1,ma);
        for (i=1;i<=ndata;i++) {

                (*funcs)(x[i],afunc,ma);
                tmp=1.0/sig[i];
                for (j=1;j<=ma;j++) {
                        u[i][j]=afunc[j]*tmp;
                }
                b[i]=y[i]*tmp;
        }
        sinfo_svd_compare(u,ndata,ma,w,v);

        wmax=0.0;
        for (j=1;j<=ma;j++)
                if (w[j] > wmax) wmax=w[j];
        thresh=TOL*wmax;
        for (j=1;j<=ma;j++) {
          if (w[j] < thresh) {
            w[j]=0.0;
            sinfo_msg_warning("SVD_FITTING detected singular value in fit !");
          }
        }
        sinfo_svb_kas(u,w,v,ndata,ma,b,a);
        *chisq=0.0;
        for (i=1;i<=ndata;i++) {
                (*funcs)(x[i],afunc,ma);
                for (sum=0.0,j=1;j<=ma;j++) sum += a[j]*afunc[j];
                *chisq += (tmp=(y[i]-sum)/sig[i],tmp*tmp);
        }
        sinfo_free_vector(afunc,1);
        sinfo_free_vector(b,1);
        sinfo_svd_variance(v,ma,w,cvm);

}
