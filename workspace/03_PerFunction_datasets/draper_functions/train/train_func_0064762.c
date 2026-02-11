ipa_dump_param_adjustments (FILE *file, ipa_parm_adjustment_vec adjustments,
			    tree fndecl)
{
  int i, len = VEC_length (ipa_parm_adjustment_t, adjustments);
  bool first = true;
  VEC(tree, heap) *parms = ipa_get_vector_of_formal_parms (fndecl);

  fprintf (file, "IPA param adjustments: ");
  for (i = 0; i < len; i++)
    {
      struct ipa_parm_adjustment *adj;
      adj = VEC_index (ipa_parm_adjustment_t, adjustments, i);

      if (!first)
	fprintf (file, "                 ");
      else
	first = false;

      fprintf (file, "%i. base_index: %i - ", i, adj->base_index);
      print_generic_expr (file, VEC_index (tree, parms, adj->base_index), 0);
      if (adj->base)
	{
	  fprintf (file, ", base: ");
	  print_generic_expr (file, adj->base, 0);
	}
      if (adj->reduction)
	{
	  fprintf (file, ", reduction: ");
	  print_generic_expr (file, adj->reduction, 0);
	}
      if (adj->new_ssa_base)
	{
	  fprintf (file, ", new_ssa_base: ");
	  print_generic_expr (file, adj->new_ssa_base, 0);
	}

      if (adj->copy_param)
	fprintf (file, ", copy_param");
      else if (adj->remove_param)
	fprintf (file, ", remove_param");
      else
	fprintf (file, ", offset %li", (long) adj->offset);
      if (adj->by_ref)
	fprintf (file, ", by_ref");
      print_node_brief (file, ", type: ", adj->type, 0);
      fprintf (file, "\n");
    }
  VEC_free (tree, heap, parms);
}
