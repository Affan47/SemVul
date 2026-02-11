sum_absolute_value() const
{
   REPORT
   Real sum1 = 0.0; Real sum2 = 0.0; Real* s = store; int nr = nrows_val;
   for (int i = 0; i<nr; i++)
   {
      int j = i;
      while (j--) sum2 += fabs(*s++);
      sum1 += fabs(*s++);
   }
   ((GeneralMatrix&)*this).tDelete(); return sum1 + 2.0 * sum2;
}
