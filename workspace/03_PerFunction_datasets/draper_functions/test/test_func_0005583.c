list_remove(list_t * list, int pos) {

   int i;

   ASSERT(list_is_ok(list));
   ASSERT(pos>=0&&pos<list->size);

   for (i = pos; i < list->size-1; i++) {
      list->move[i] = list->move[i+1];
      list->value[i] = list->value[i+1];
   }

   list->size--;
}
