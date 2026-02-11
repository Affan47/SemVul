add_infinity(sge_rlim_t rlim, sge_rlim_t offset)
{
   if (rlim == RLIM_INFINITY || offset == RLIM_INFINITY) {
      return RLIM_INFINITY;
   }

   if ((sge_rlim_t)(RLIM_MAX-offset) < rlim) {
      rlim = RLIM_INFINITY;
   } else {
      rlim += offset;
   }

   return rlim;
}
