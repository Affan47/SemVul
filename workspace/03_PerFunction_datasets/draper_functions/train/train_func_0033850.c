init_sym()
   {
   static int first_time = 1;
   int hash_val;
   register struct sym_entry *sym;
   int i;


   if (first_time) {
      first_time = 0;
      for (i = 0; i < HashSize; ++i)
         sym_tbl[i] = NULL;
      dcl_stk = NewStruct(lvl_entry);
      dcl_stk->nest_lvl = 1;
      dcl_stk->next = NULL;
      block = spec_str(block);
      descrip = spec_str(descrip);
      }
   else {
      for (hash_val = 0; hash_val < HashSize; ++ hash_val) {
         for (sym = sym_tbl[hash_val]; sym != NULL &&
           sym->nest_lvl > 0; sym = sym_tbl[hash_val]) {
            sym_tbl[hash_val] = sym->next;
            free((char *)sym);
            }
         }
      }
   dcl_stk->kind_dcl = OtherDcl;
   dcl_stk->parms_done = 0;
   }
