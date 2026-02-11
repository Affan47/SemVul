Next_small(Real mu)
{


   if (mu < 10) return Next_very_small(mu);
   int k_start = (int)mu;  Real u = U.Next();
   Real t1 = exp(k_start * log(mu) - mu - ln_gamma(k_start+1));
   if (t1 > u) return k_start;
   int k1 = k_start; int k2 = k_start; Real t2 = t1; Real s = t1;
   for(;;)
   {
      ++k1; t1 *= mu / k1; s += t1; if (s > u) return k1;
      if (k2 > 0) { t2 *= k2 / mu; --k2; s += t2; if (s > u) return k2; }
   }
}
