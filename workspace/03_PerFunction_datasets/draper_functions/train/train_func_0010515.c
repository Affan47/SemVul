mrg_locs(locs)
struct val_loc **locs;
   {
   int i;

   for (i = 0; i < nsyms; ++i)
      if (cur_symtab[i].loc == NULL)
         cur_symtab[i].loc = locs[i];
   free((char *)locs);
   }
