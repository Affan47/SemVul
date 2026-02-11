dlist_insl_end(dlist_head_t *head,
      dlist_t *dlist) {
   if (!head || !dlist)
      return 0;

   if (!head->dlist || !head->end) {
      head->dlist = dlist;
      head->end  = dlist;
      head->num  = 1;
      return 1;
   } else {
      return dlist_insl_after(head, head->end, dlist);
   }
}
