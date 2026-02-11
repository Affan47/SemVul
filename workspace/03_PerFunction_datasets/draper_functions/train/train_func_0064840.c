operator/(const BigInt& x, const BigInt& y)
   {
   BigInt q, r;
   divide(x, y, q, r);
   return q;
   }
