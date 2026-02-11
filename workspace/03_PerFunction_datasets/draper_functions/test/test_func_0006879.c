find_entry(const board_t * board, int move) {

   uint64 key;
   int index;
   int pos;

   ASSERT(board!=NULL);
   ASSERT(move_is_ok(move));

   ASSERT(move_is_legal(move,board));


   key = board->key;


   for (index = key & Book->mask; (pos=Book->hash[index]) != NIL; index = (index+1) & Book->mask) {

      ASSERT(pos>=0&&pos<Book->size);

      if (Book->entry[pos].key == key && Book->entry[pos].move == move) {
         return pos;
      }
   }


   ASSERT(Book->size<=Book->alloc);

   if (Book->size == Book->alloc) {


      resize();

      for (index = key & Book->mask; Book->hash[index] != NIL; index = (index+1) & Book->mask)
         ;
   }


   ASSERT(Book->size<Book->alloc);
   pos = Book->size++;

   Book->entry[pos].key = key;
   Book->entry[pos].move = move;
   Book->entry[pos].n = 0;
   Book->entry[pos].sum = 0;
   Book->entry[pos].colour = board->turn;


   ASSERT(index>=0&&index<Book->alloc*2);
   ASSERT(Book->hash[index]==NIL);
   Book->hash[index] = pos;

   ASSERT(pos>=0&&pos<Book->size);

   return pos;
}
