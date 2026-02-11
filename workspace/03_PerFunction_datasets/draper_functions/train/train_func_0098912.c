operator-(const BigInt& x, const BigInt& y)
   {
   const u32bit x_sw = x.sig_words(), y_sw = y.sig_words();

   s32bit relative_size = bigint_cmp(x.data(), x_sw, y.data(), y_sw);

#ifdef BOTAN_TYPES_QT
   BigInt z(BigInt::Positive, qMax(x_sw, y_sw) + 1);
#else
   BigInt z(BigInt::Positive, std::max(x_sw, y_sw) + 1);
#endif

   if(relative_size < 0)
      {
      if(x.sign() == y.sign())
         bigint_sub3(z.get_reg(), y.data(), y_sw, x.data(), x_sw);
      else
         bigint_add3(z.get_reg(), x.data(), x_sw, y.data(), y_sw);
      z.set_sign(y.reverse_sign());
      }
   else if(relative_size == 0)
      {
      if(x.sign() != y.sign())
         bigint_shl2(z.get_reg(), x.data(), x_sw, 0, 1);
      }
   else if(relative_size > 0)
      {
      if(x.sign() == y.sign())
         bigint_sub3(z.get_reg(), x.data(), x_sw, y.data(), y_sw);
      else
         bigint_add3(z.get_reg(), x.data(), x_sw, y.data(), y_sw);
      z.set_sign(x.sign());
      }
   return z;
   }
