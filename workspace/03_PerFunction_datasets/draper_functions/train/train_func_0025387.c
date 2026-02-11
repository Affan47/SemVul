insert_relation(linalg_t * la_inf, poly_t * poly_inf, mpz_t Y)
{
   la_col_t * unmerged = la_inf->unmerged;
   unsigned long num_unmerged = la_inf->num_unmerged;

   unsigned long * small = la_inf->small;
   const unsigned long num_factors = la_inf->num_factors;
   fac_t * factor = la_inf->factor;

   unsigned long * curr_rel = la_inf->curr_rel;

   unsigned long fac_num = 0;
   clear_col(unmerged + num_unmerged);

   for (unsigned long i = 0; i < SMALL_PRIMES; i++)
   {
       if (small[i] & 1) insert_col_entry(unmerged + num_unmerged, i);
       if (small[i])
       {
          curr_rel[2*fac_num + 1] = i;
          curr_rel[2*fac_num + 2] = small[i];
          fac_num++;
       }
   }
   for (unsigned long i = 0; i < num_factors; i++)
   {
       if (factor[i].exp & 1) insert_col_entry(unmerged + num_unmerged, factor[i].ind);
       curr_rel[2*fac_num + 1] = factor[i].ind;
       curr_rel[2*fac_num + 2] = factor[i].exp;
       fac_num++;
   }
   curr_rel[0] = fac_num;

   unmerged[num_unmerged].orig = la_inf->num_relations;

   mpz_set(la_inf->Y_arr[la_inf->num_relations], Y);

   la_inf->curr_rel += MAX_FACS*2;
   la_inf->num_unmerged++;
   la_inf->num_relations++;

   if (la_inf->num_unmerged == 100)
   {
      return merge_relations(la_inf);
   }

   return 0;
}
