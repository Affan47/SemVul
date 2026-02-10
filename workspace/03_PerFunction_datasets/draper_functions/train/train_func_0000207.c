trace() const
{
   REPORT
   int i = nrows_val; int w = lower_val+upper_val+1;
   Real sum = 0.0; Real* s = store+lower_val;

   if (i) for (;;) { sum += *s; if (!(--i)) break; s += w; }
   ((GeneralMatrix&)*this).tDelete(); return sum;
}
