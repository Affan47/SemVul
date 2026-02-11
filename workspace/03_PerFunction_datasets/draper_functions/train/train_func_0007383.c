object_set_range_id(lListElem *object, int rnm, u_long32 start, u_long32 end,
                    u_long32 step)
{
   lListElem *range_elem;
   int ret = 0;

   range_elem = lFirst(lGetList(object, rnm));
   if (range_elem == NULL) {
      lList *range_list;

      range_elem = lCreateElem(RN_Type);
      range_list = lCreateList("task_id_range", RN_Type);
      if (range_elem == NULL || range_list == NULL) {
         lFreeElem(&range_elem);
         lFreeList(&range_list);


         ret = 1;
      } else {
         lAppendElem(range_list, range_elem);
         lSetList(object, rnm, range_list);
      }
   }
   if (range_elem != NULL) {
      lSetUlong(range_elem, RN_min, start);
      lSetUlong(range_elem, RN_max, end);
      lSetUlong(range_elem, RN_step, step);
   }
   return ret;
}
