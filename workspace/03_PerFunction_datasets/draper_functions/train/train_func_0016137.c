log_determinant() const
{
   REPORT
   int i = nrows_val; LogAndSign sum;
   Real* s = store + lower_val; int j = lower_val + 1;

   if (i) for (;;) { sum *= *s; if (!(--i)) break; s += j; }
   ((GeneralMatrix&)*this).tDelete(); return sum;
}
