fini_ssa_operands (void)
{
  struct ssa_operand_memory_d *ptr;

  if (!--n_initialized)
    {
      VEC_free (tree, heap, build_defs);
      VEC_free (tree, heap, build_uses);
      build_vdef = NULL_TREE;
      build_vuse = NULL_TREE;
    }

  gimple_ssa_operands (cfun)->free_defs = NULL;
  gimple_ssa_operands (cfun)->free_uses = NULL;

  while ((ptr = gimple_ssa_operands (cfun)->operand_memory) != NULL)
    {
      gimple_ssa_operands (cfun)->operand_memory
	= gimple_ssa_operands (cfun)->operand_memory->next;
      ggc_free (ptr);
    }

  gimple_ssa_operands (cfun)->ops_active = false;

  if (!n_initialized)
    bitmap_obstack_release (&operands_bitmap_obstack);

  cfun->gimple_df->vop = NULL_TREE;

  if (dump_file && (dump_flags & TDF_STATS))
    {
      fprintf (dump_file, "Original clobbered vars:           %d\n",
	       clobber_stats.clobbered_vars);
      fprintf (dump_file, "Static write clobbers avoided:     %d\n",
	       clobber_stats.static_write_clobbers_avoided);
      fprintf (dump_file, "Static read clobbers avoided:      %d\n",
	       clobber_stats.static_read_clobbers_avoided);
      fprintf (dump_file, "Unescapable clobbers avoided:      %d\n",
	       clobber_stats.unescapable_clobbers_avoided);
      fprintf (dump_file, "Original read-only clobbers:       %d\n",
	       clobber_stats.readonly_clobbers);
      fprintf (dump_file, "Static read-only clobbers avoided: %d\n",
	       clobber_stats.static_readonly_clobbers_avoided);
    }
}
