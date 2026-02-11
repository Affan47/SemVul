ZNP_mpn_mulmid (mp_limb_t* res, const mp_limb_t* op1, size_t n1,
                const mp_limb_t* op2, size_t n2)
{
   ZNP_ASSERT (n1 >= n2);
   ZNP_ASSERT (n2 >= 1);

   if (n2 >= ZNP_mpn_mulmid_fallback_thresh)
   {
      ZNP_mpn_mulmid_fallback (res, op1, n1, op2, n2);
      return;
   }


   ZNP_mpn_smp (res, op1, n1, op2, n2);

#if GMP_NAIL_BITS == 0  &&  ULONG_BITS == GMP_NUMB_BITS


   if (res[1] >= -(mp_limb_t)(n2))
      ZNP_mpn_mulmid_fallback (res, op1, n1, op2, n2);

#else
#error Not nails-safe yet
#endif
}
