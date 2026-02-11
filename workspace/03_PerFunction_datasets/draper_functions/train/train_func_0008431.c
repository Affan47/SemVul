free_loop_data (struct ivopts_data *data)
{
  unsigned i, j;
  bitmap_iterator bi;
  tree obj;

  if (data->niters)
    {
      pointer_map_traverse (data->niters, free_tree_niter_desc, NULL);
      pointer_map_destroy (data->niters);
      data->niters = NULL;
    }

  EXECUTE_IF_SET_IN_BITMAP (data->relevant, 0, i, bi)
    {
      struct version_info *info;

      info = ver_info (data, i);
      if (info->iv)
	free (info->iv);
      info->iv = NULL;
      info->has_nonlin_use = false;
      info->preserve_biv = false;
      info->inv_id = 0;
    }
  bitmap_clear (data->relevant);
  bitmap_clear (data->important_candidates);

  for (i = 0; i < n_iv_uses (data); i++)
    {
      struct iv_use *use = iv_use (data, i);

      free (use->iv);
      BITMAP_FREE (use->related_cands);
      for (j = 0; j < use->n_map_members; j++)
	if (use->cost_map[j].depends_on)
	  BITMAP_FREE (use->cost_map[j].depends_on);
      free (use->cost_map);
      free (use);
    }
  VEC_truncate (iv_use_p, data->iv_uses, 0);

  for (i = 0; i < n_iv_cands (data); i++)
    {
      struct iv_cand *cand = iv_cand (data, i);

      if (cand->iv)
	free (cand->iv);
      if (cand->depends_on)
	BITMAP_FREE (cand->depends_on);
      free (cand);
    }
  VEC_truncate (iv_cand_p, data->iv_candidates, 0);

  if (data->version_info_size < num_ssa_names)
    {
      data->version_info_size = 2 * num_ssa_names;
      free (data->version_info);
      data->version_info = XCNEWVEC (struct version_info, data->version_info_size);
    }

  data->max_inv_id = 0;

  FOR_EACH_VEC_ELT (tree, decl_rtl_to_reset, i, obj)
    SET_DECL_RTL (obj, NULL_RTX);

  VEC_truncate (tree, decl_rtl_to_reset, 0);

  htab_empty (data->inv_expr_tab);
  data->inv_expr_id = 0;
}
