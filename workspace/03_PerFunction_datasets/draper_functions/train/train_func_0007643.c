compute_ae_kill (sbitmap *ae_gen, sbitmap *ae_kill,
		 struct hash_table *expr_hash_table)
{
  basic_block bb;
  unsigned int i;
  struct expr *expr;

  FOR_EACH_BB (bb)
    for (i = 0; i < expr_hash_table->size; i++)
      for (expr = expr_hash_table->table[i]; expr; expr = expr->next_same_hash)
	{

	  if (TEST_BIT (ae_gen[bb->index], expr->bitmap_index))
	    continue;

	  if (expr_killed_p (expr->expr, bb))
	    SET_BIT (ae_kill[bb->index], expr->bitmap_index);
	}
}
