check_dat(fstat, frep, fcur, min_t, max_t, results)
FILE *fstat, *frep;
struct file_list *fcur;
int min_t, max_t;
struct hom *results;
{
   struct best_block *block, *lblock, *fblock;
   int i, nblk, nrep;

   nblk = 0;
   block = fblock = lblock = NULL;


   while ( (block = read_block(fcur->fdat, results[min_t].fam)) != NULL)
   {
      if (nblk > 0) lblock->next_block = block;
      else fblock = block;
      nblk++;
      lblock=block;
   }
   if (fblock == NULL) return(0);


   fcur->prevAC = fblock->dat_pos;


   add_query(fstat, min_t, max_t, results, fblock);


   i = nrep = 0;
   while (i < NRepeat &&
          strcasecmp(Repeats[i].ac, results[min_t].fam) <= 0)
      i++;
   if (i > 0 && strcasecmp(Repeats[i-1].ac, results[min_t].fam) == 0 &&
       Repeats[i-1].num > 1)
            nrep = check_repeats(frep, min_t, max_t, results, Repeats[i-1].num - 1);


   if (nblk > 1)
            map_blocks(min_t, max_t, results, fblock);
   else printf("\n");


   align_blocks(min_t, max_t, results, fblock);


   block = fblock;
   while (block != NULL)
   {
      lblock = block;
      block = block->next_block;
      free(lblock);
   }

   return(nblk);
}
