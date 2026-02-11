percent_equal( double n1, double n2, double rel_error)
{
   double val1, val2;

   val1 = 0.5 * rel_error * (fabs( n1) + fabs( n2));
   val2 = fabs( n1 - n2);
   if (val1 >= val2)
      return(TRUE);
   else
     return(FALSE);
}
