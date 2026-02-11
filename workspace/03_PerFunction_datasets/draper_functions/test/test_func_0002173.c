dlist_insl_front(dlist_head_t *head,
      dlist_t *dlist) {
   if (!head || !dlist)
      return 0;

   if (!head->dlist) {
      head->dlist = dlist;
      head->end  = dlist;
      head->num  = 1;
      return 1;
   } else {
      return dlist_insl_before(head, head->dlist, dlist);
   }
}
