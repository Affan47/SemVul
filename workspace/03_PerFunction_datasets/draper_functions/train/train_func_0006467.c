dListRemove (DList* pList, DListNode* node)
{
   if(node->next != 0) {
      node->next->prev = node->prev;
   }
   else {
      pList->tail = node->prev;
   }
   if(node->prev != 0) {
      node->prev->next = node->next;
   }
   else {
      pList->head = node->next;
   }
   pList->count--;
}
