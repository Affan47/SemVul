qim_list_trash_all_of_type_X(lList **this_list, u_long32 type)
{
   bool ret = true;

   DENTER(TOP_LAYER, "qim_list_trash_all_of_type_X");
   if (this_list != NULL) {
      lListElem *elem = NULL;
      lListElem *next_elem = NULL;

      next_elem = lFirst(*this_list);
      while ((elem = next_elem) != NULL) {
         u_long32 elem_type = lGetUlong(elem, QIM_type);

         next_elem = lNext(elem);
         if ((elem_type & type) != 0) {
            lRemoveElem(*this_list, &elem);
         }
      }
      if (lGetNumberOfElem(*this_list) == 0) {
         lFreeList(this_list);
      }
   }
   DEXIT;
   return ret;
}
