insert_set_in_table (x, insn, table)
     rtx x;
     rtx insn;
     struct hash_table *table;
{
  int found;
  unsigned int hash;
  struct expr *cur_expr, *last_expr = NULL;
  struct occr *cur_occr, *last_occr = NULL;

  if (GET_CODE (x) != SET
      || GET_CODE (SET_DEST (x)) != REG)
    abort ();

  hash = hash_set (REGNO (SET_DEST (x)), table->size);

  cur_expr = table->table[hash];
  found = 0;

  while (cur_expr && 0 == (found = expr_equiv_p (cur_expr->expr, x)))
    {


      last_expr = cur_expr;
      cur_expr = cur_expr->next_same_hash;
    }

  if (! found)
    {
      cur_expr = (struct expr *) gcse_alloc (sizeof (struct expr));
      bytes_used += sizeof (struct expr);
      if (table->table[hash] == NULL)

	table->table[hash] = cur_expr;
      else

	last_expr->next_same_hash = cur_expr;


      cur_expr->expr = copy_rtx (x);
      cur_expr->bitmap_index = table->n_elems++;
      cur_expr->next_same_hash = NULL;
      cur_expr->antic_occr = NULL;
      cur_expr->avail_occr = NULL;
    }


  cur_occr = cur_expr->avail_occr;


  while (cur_occr && BLOCK_NUM (cur_occr->insn) != BLOCK_NUM (insn))
    {


      last_occr = cur_occr;
      cur_occr = cur_occr->next;
    }

  if (cur_occr)


    cur_occr->insn = insn;
  else
    {

      cur_occr = (struct occr *) gcse_alloc (sizeof (struct occr));
      bytes_used += sizeof (struct occr);


      if (cur_expr->avail_occr == NULL)
	cur_expr->avail_occr = cur_occr;
      else
	last_occr->next = cur_occr;

      cur_occr->insn = insn;
      cur_occr->next = NULL;
    }
}
