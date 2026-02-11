check_dat(min_t, max_t, results, fblock)
int min_t, max_t;
struct hom *results;
struct best_block *fblock;
{
   int nblock;


   nblock = add_query(min_t, max_t, results, fblock);


   if (nblock > 1) map_blocks(min_t, max_t, results, fblock);
   else            printf("\n");


   align_blocks(fblock);

}
