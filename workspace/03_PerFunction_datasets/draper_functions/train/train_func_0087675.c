ReverseElements()
{

   REPORT
   int n = Storage(); Real* x = Store(); Real* rx = x + n;
   n /= 2;
   while (n--) { Real t = *(--rx); *rx = *x; *(x++) = t; }
}
