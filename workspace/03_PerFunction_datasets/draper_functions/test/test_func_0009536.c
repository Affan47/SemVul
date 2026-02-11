minimum1(int& i) const
{
   REPORT
   if (storage == 0) NullMatrixError(this);
   int l = storage - 1; Real* s = store; Real minval = *s++; int li = l;
   while (l--) { Real a = *s++; if (minval >= a) { minval = a; li = l; } }
   i = storage - li;
   ((GeneralMatrix&)*this).tDelete(); return minval;
}
