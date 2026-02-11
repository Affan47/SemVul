eina_inlist_sorted_state_init(Eina_Inlist_Sorted_State *state, Eina_Inlist *list)
{
   Eina_Inlist *ct = NULL;
   int count = 0;
   int jump_count = 1;


   for (ct = list; ct; ct = ct->next, jump_count++, count++)
     {
        if (jump_count == state->jump_div)
          {
             if (state->jump_limit == EINA_INLIST_JUMP_SIZE)
               {
                  _eina_inlist_sorted_state_compact(state);
               }

             state->jump_table[state->jump_limit] = ct;
             state->jump_limit++;
             jump_count = 0;
          }
     }

   state->inserted = count;
   return count;
}
