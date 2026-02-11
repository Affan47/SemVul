z_sqrtmod(unsigned long a, unsigned long p)
{
     unsigned int r, k, m;
     unsigned long p1, b, g, bpow, gpow, res;
     double pinv;

     if ((a==0) || (a==1))
     {
        return a;
     }

     pinv = z_precompute_inverse(p);

     if (z_jacobi_precomp(a, p, pinv) == -1) return 0;

     if ((p&3)==3)
     {
        return z_powmod2_precomp(a, (p+1)/4, p, pinv);
     }

     r = 0;
     p1 = p-1;

     do {
        p1>>=1UL;
        r++;
     } while ((p1&1UL) == 0);

     b = z_powmod2_precomp(a, p1, p, pinv);

     for (k=2UL; ;k++)
     {
         if (z_jacobi_precomp(k, p, pinv) == -1) break;
     }

     g = z_powmod2_precomp(k, p1, p, pinv);
     res = z_powmod2_precomp(a, (p1+1)/2, p, pinv);
     if (b == 1UL)
     {
        return res;
     }

     while (b != 1)
     {
           bpow = b;
           for (m = 1; (m <= r-1) && (bpow != 1); m++)
           {
               bpow = z_mulmod2_precomp(bpow, bpow, p, pinv);
           }
           gpow = g;
           for (int i = 1; i < r-m; i++)
           {
               gpow = z_mulmod2_precomp(gpow, gpow, p, pinv);
           }
           res = z_mulmod2_precomp(res, gpow, p, pinv);
           gpow = z_mulmod2_precomp(gpow, gpow, p, pinv);
           b = z_mulmod2_precomp(b, gpow, p, pinv);
           gpow = g;
           r = m;
     }

     return res;
}
