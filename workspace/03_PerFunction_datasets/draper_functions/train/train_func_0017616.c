darray_snatch(DArray *da, int i) {
   void *v;
   if (i >= 0 && i < da->len) {
      v = da->items[i];
      da->items[i] = NULL;
      return v;
   }
   else return NULL;
}
