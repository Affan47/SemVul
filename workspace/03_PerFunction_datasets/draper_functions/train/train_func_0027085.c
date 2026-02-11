dump_var (variable var)
{
  int i;
  location_chain node;

  if (dv_is_decl_p (var->dv))
    {
      const_tree decl = dv_as_decl (var->dv);

      if (DECL_NAME (decl))
	{
	  fprintf (dump_file, "  name: %s",
		   IDENTIFIER_POINTER (DECL_NAME (decl)));
	  if (dump_flags & TDF_UID)
	    fprintf (dump_file, "D.%u", DECL_UID (decl));
	}
      else if (TREE_CODE (decl) == DEBUG_EXPR_DECL)
	fprintf (dump_file, "  name: D#%u", DEBUG_TEMP_UID (decl));
      else
	fprintf (dump_file, "  name: D.%u", DECL_UID (decl));
      fprintf (dump_file, "\n");
    }
  else
    {
      fputc (' ', dump_file);
      print_rtl_single (dump_file, dv_as_value (var->dv));
    }

  for (i = 0; i < var->n_var_parts; i++)
    {
      fprintf (dump_file, "    offset %ld\n",
	       (long)(var->onepart ? 0 : VAR_PART_OFFSET (var, i)));
      for (node = var->var_part[i].loc_chain; node; node = node->next)
	{
	  fprintf (dump_file, "      ");
	  if (node->init == VAR_INIT_STATUS_UNINITIALIZED)
	    fprintf (dump_file, "[uninit]");
	  print_rtl_single (dump_file, node->loc);
	}
    }
}
