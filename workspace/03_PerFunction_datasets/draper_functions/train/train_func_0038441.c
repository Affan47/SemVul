mp_fread(mp_int *a, int radix, FILE *stream)
{
   int err, ch, neg, y;


   mp_zero(a);


   ch = fgetc(stream);
   if (ch == '-') {
      neg = MP_NEG;
      ch = fgetc(stream);
   } else {
      neg = MP_ZPOS;
   }

   for (;;) {

      for (y = 0; y < radix; y++) {
          if (mp_s_rmap[y] == ch) {
             break;
          }
      }
      if (y == radix) {
         break;
      }


      if ((err = mp_mul_d(a, radix, a)) != MP_OKAY) {
         return err;
      }
      if ((err = mp_add_d(a, y, a)) != MP_OKAY) {
         return err;
      }

      ch = fgetc(stream);
   }
   if (mp_cmp_d(a, 0) != MP_EQ) {
      a->sign = neg;
   }

   return MP_OKAY;
}
