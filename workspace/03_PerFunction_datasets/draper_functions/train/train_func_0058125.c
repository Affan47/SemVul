delete_tree_ssa (void)
{
  referenced_var_iterator rvi;
  tree var;


  FOR_EACH_REFERENCED_VAR (cfun, var, rvi)
    {
      if (is_global_var (var))
	continue;
      if (var_ann (var))
	{
	  ggc_free (var_ann (var));
	  *DECL_VAR_ANN_PTR (var) = NULL;
	}
    }
  htab_delete (gimple_referenced_vars (cfun));
  cfun->gimple_df->referenced_vars = NULL;

  fini_ssanames ();
  fini_phinodes ();


  if (ssa_operands_active ())
    fini_ssa_operands ();

  htab_delete (cfun->gimple_df->default_defs);
  cfun->gimple_df->default_defs = NULL;
  pt_solution_reset (&cfun->gimple_df->escaped);
  if (cfun->gimple_df->decls_to_pointers != NULL)
    pointer_map_destroy (cfun->gimple_df->decls_to_pointers);
  cfun->gimple_df->decls_to_pointers = NULL;
  cfun->gimple_df->modified_noreturn_calls = NULL;
  cfun->gimple_df = NULL;


  redirect_edge_var_map_destroy ();
}
