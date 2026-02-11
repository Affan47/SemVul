eliminate_phi (e, reg_partition)
     edge e;
     partition reg_partition;
{
  int n_nodes;
  sbitmap *pred, *succ;
  sbitmap visited;
  rtx *nodes;
  int *stack, *tstack;
  rtx insn;
  int i;


  insn = first_insn_after_basic_block_note (e->dest);

  n_nodes = 0;
  while (PHI_NODE_P (insn))
    {
      insn = next_nonnote_insn (insn);
      n_nodes += 2;
    }

  if (n_nodes == 0)
    return;


  nodes = (rtx *) alloca (n_nodes * sizeof(rtx));
  pred = sbitmap_vector_alloc (n_nodes, n_nodes);
  succ = sbitmap_vector_alloc (n_nodes, n_nodes);
  sbitmap_vector_zero (pred, n_nodes);
  sbitmap_vector_zero (succ, n_nodes);

  insn = first_insn_after_basic_block_note (e->dest);

  n_nodes = 0;
  for (; PHI_NODE_P (insn); insn = next_nonnote_insn (insn))
    {
      rtx* preg = phi_alternative (PATTERN (insn), e->src->index);
      rtx tgt = SET_DEST (PATTERN (insn));
      rtx reg;


      if (preg == NULL)
	continue;
      reg = *preg;

      if (GET_CODE (reg) != REG || GET_CODE (tgt) != REG)
	abort ();

      reg = regno_reg_rtx[partition_find (reg_partition, REGNO (reg))];
      tgt = regno_reg_rtx[partition_find (reg_partition, REGNO (tgt))];


      if (reg != tgt)
	{
	  int ireg, itgt;

	  ireg = ephi_add_node (reg, nodes, &n_nodes);
	  itgt = ephi_add_node (tgt, nodes, &n_nodes);

	  SET_BIT (pred[ireg], itgt);
	  SET_BIT (succ[itgt], ireg);
	}
    }

  if (n_nodes == 0)
    goto out;


  visited = sbitmap_alloc (n_nodes);
  sbitmap_zero (visited);

  tstack = stack = (int *) alloca (n_nodes * sizeof (int));

  for (i = 0; i < n_nodes; ++i)
    if (! TEST_BIT (visited, i))
      tstack = ephi_forward (i, visited, succ, tstack);

  sbitmap_zero (visited);


  start_sequence ();

  while (tstack != stack)
    {
      i = *--tstack;
      if (! TEST_BIT (visited, i))
	ephi_create (i, visited, pred, succ, nodes);
    }

  insn = get_insns ();
  end_sequence ();
  insert_insn_on_edge (insn, e);
  if (rtl_dump_file)
    fprintf (rtl_dump_file, "Emitting copy on edge (%d,%d)\n",
	     e->src->index, e->dest->index);

  sbitmap_free (visited);
out:
  sbitmap_vector_free (pred);
  sbitmap_vector_free (succ);
}
