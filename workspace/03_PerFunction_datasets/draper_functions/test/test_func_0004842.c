mypow(n, exposant)
double n, exposant;
{
   int i;
   double res;

   res = 1.0;
   if (exposant > 0)
      for (i = 0; i < exposant; i++)
         res *= n;
   else  for (i = 0; i < -exposant; i++)
         res /= n;
   return (res);
}
