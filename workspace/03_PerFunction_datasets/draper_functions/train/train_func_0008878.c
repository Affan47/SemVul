ia_deque_rtn_q (IARTN_Q *que) {
   IARTN_Q *tmpdata;
   if (que->next == NULL)
      return NULL;
   tmpdata = que->next;
   if ( que->next == que->tail)
      que->next = que->tail = NULL;
   else
      que->next = que->next->next;
   return tmpdata;
}
