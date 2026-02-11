sum_absolute_value() const
{
   REPORT
   Real sum = 0.0; int i = storage; Real* s = store;
   while (i--) sum += fabs(*s++);
   ((GeneralMatrix&)*this).tDelete(); return sum;
}
