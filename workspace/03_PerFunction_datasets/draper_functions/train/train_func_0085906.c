range_set_all_ids(lListElem *range, u_long32 min, u_long32 max,
                       u_long32 step)
{
   DENTER(RANGE_LAYER, "range_set_all_ids");
   if (range != NULL) {
      lSetUlong(range, RN_min, min);
      lSetUlong(range, RN_max, max);
      if (min != max) {
         lSetUlong(range, RN_step, step);
      } else {
         lSetUlong(range, RN_step, 1);
      }
   }
   DRETURN_VOID;
}
