find_val(int     *a,
                int     n,
                int     key,
                double  *val)
{
   int   j = 0;
   int   jlo = -1;
   int   jup = n;

   if (key < a[0] || key > a[n-1]) {return(0.0);}

   while (jup-jlo > 1)
   {
      j = (jlo+jup) >> 1;
      if (key >= a[j]) {jlo = j;}
      else {jup = j;}
   }

   if (a[jlo] == key) {return(val[jlo]);}
   else return(0.0);
}
