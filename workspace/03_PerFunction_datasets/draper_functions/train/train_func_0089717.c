search_update_sort() {

   int size;
   int i, j;
   search_best_t swap;

   ASSERT(SearchRoot->move_nb>0);


   size = SearchRoot->move_nb;
   SearchBest[size].value = -32768;
   SearchBest[size].depth = -128;


   for (i = size-1; i >= 0; i--) {

      swap = SearchBest[i];

      for (j = i; swap.value < SearchBest[j+1].value && swap.depth <= SearchBest[j+1].depth; j++) {
         SearchBest[j] = SearchBest[j+1];
      }

      ASSERT(j<size);

      SearchBest[j] = swap;
   }


   if (DEBUG) {
      for (i = 0; i < size-1; i++) {
         ASSERT(SearchBest[i].value>=SearchBest[i+1].value||
                SearchBest[i].depth>SearchBest[i+1].depth);
      }
   }
}
