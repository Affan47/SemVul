operator[](int i)
{
   REPORT
   if (i < 0 || i >= n) Throw(Logic_error("array index out of range"));
   return a[i];
}
