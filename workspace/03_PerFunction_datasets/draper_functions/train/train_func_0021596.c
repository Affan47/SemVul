tt_lookup(state *s)
{
   ull board_u, board_l;
   int hash_index;
   int found = 0;
   int max = 0;

   if (tt == NULL)
      tt = (state_t **) calloc(TT, sizeof(state_t *));


   board_u = s->white_bd[1] | s->black_bd[1] | s->blocks_bd[1];
   board_l = s->white_bd[0] | s->black_bd[0] | s->blocks_bd[0];

   hash_index = (board_u ^ board_l) % TT;

   while(tt[hash_index] && !found && (max < MAX_TT_SEARCH) && (hash_index < TT))
     {
      found = tt_compare(s,tt[hash_index]);
      ++hash_index;
      ++max;
     }

   ++tt_lookups;
   if (found)
     {
      ++tt_lookup_finds;
      return (tt[--hash_index]);


     }
   else
      return NULL;

}
