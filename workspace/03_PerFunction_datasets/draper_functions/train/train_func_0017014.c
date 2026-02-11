cover4(int n, double a[], double b, double u, double x[],
      double y, int cov[], double *_alfa, double *_beta)
{
      int i, j, k, l, try = 0, ret = 0;
      double eps, alfa, beta, temp, rmax = 0.001;
      eps = 0.001 * (1.0 + fabs(b));
      for (i = 0+1; i <= n; i++)
      for (j = i+1; j <= n; j++)
      for (k = j+1; k <= n; k++)
      for (l = k+1; l <= n; l++)
      {
         try++;
         if (try > MAXTRY) goto done;

         if (a[i] + a[j] + a[k] + a[l] + y > b + eps)
         {
            temp = a[i] + a[j] + a[k] + a[l] - b;
            alfa = 1.0 / (temp + u);
            beta = 4.0 - alfa * temp;

            temp = x[i] + x[j] + x[k] + x[l] + alfa * y - beta;

            if (rmax < temp)
            {  rmax = temp;
               cov[1] = i;
               cov[2] = j;
               cov[3] = k;
               cov[4] = l;
               *_alfa = alfa;
               *_beta = beta;
               ret = 1;
            }
         }
      }
done: return ret;
}
