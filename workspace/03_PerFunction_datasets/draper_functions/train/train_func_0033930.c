utilization_queue_end(const lListElem *cr, bool for_excl_request)
{
   const lListElem *ep = lLast(lGetList(cr, RUE_utilized));
   double max = 0.0;

   DENTER(TOP_LAYER, "utilization_queue_end");

#if 1
   utilization_print(cr, "the object");
#endif

   if (ep) {
      if (lGetUlong(ep, RDE_time) != U_LONG32_MAX) {
         max = lGetDouble(ep, RDE_amount);
      } else {
         max = lGetDouble(lPrev(ep), RDE_amount);
      }
   }

   if (for_excl_request) {
      double max_nonexclusive;
      ep = lLast(lGetList(cr, RUE_utilized_nonexclusive));
      if (ep) {
         if (lGetUlong(ep, RDE_time) != U_LONG32_MAX) {
            max_nonexclusive = lGetDouble(ep, RDE_amount);
         } else {
            max_nonexclusive = lGetDouble(lPrev(ep), RDE_amount);
         }
         max = MAX(max, max_nonexclusive);
      }
   }

   DPRINTF(("returning %f\n", max));
   DRETURN(max);
}
