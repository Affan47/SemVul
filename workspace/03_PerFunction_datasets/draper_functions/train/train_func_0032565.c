cmatinv( complex *x, int n, int m, double *space)
{


   int i,j,k, *irow=(int*) space;
   double xmaxsize, ee=1e-20;
   complex xmax, t,t1;

   For(i,n)  {
       xmaxsize = 0.;
       for (j=i; j<n; j++) {
          if ( xmaxsize < csize (x[j*m+i]))  {
               xmaxsize = csize (x[j*m+i]);
               xmax = x[j*m+i];
               irow[i] = j;
          }
       }
       if (xmaxsize < ee)   {
           printf("\nDet goes to zero at %8d!\t\n", i+1);
           return(-1);
       }
       if (irow[i] != i) {
           For(j,m) {
                t = x[i*m+j];
                x[i*m+j] = x[irow[i]*m+j];
                x[ irow[i]*m+j] = t;
           }
       }
       t = cdiv (compl(1,0), x[i*m+i]);
       For(j,n) {
           if (j == i) continue;
           t1 = cby (t,x[j*m+i]);
           For(k,m)  x[j*m+k] = cminus (x[j*m+k], cby(t1,x[i*m+k]));
           x[j*m+i] = cfactor (t1, -1);
       }
       For(j,m)   x[i*m+j] = cby (x[i*m+j], t);
       x[i*m+i] = t;
   }
   for (i=n-1; i>=0; i--) {
        if (irow[i] == i) continue;
        For(j,n)  {
           t = x[j*m+i];
           x[j*m+i] = x[j*m+irow[i]];
           x[ j*m+irow[i]] = t;
        }
   }
   return (0);
}
