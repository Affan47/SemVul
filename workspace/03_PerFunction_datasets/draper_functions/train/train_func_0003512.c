is_in_book(const board_t * board) {

   int pos;
   entry_t entry[1];

   ASSERT(board!=NULL);

   for (pos = find_pos(board->key); pos < BookSize; pos++) {
      read_entry(entry,pos);
      if (entry->key == board->key) return true;
   }

   return false;
}
