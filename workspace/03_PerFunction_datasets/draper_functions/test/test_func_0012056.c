ipa_get_indirect_edge_target (struct cgraph_edge *ie,
			      VEC (tree, heap) *known_vals,
			      VEC (tree, heap) *known_binfos)
{
  int param_index = ie->indirect_info->param_index;
  HOST_WIDE_INT token, anc_offset;
  tree otr_type;
  tree t;

  if (param_index == -1)
    return NULL_TREE;

  if (!ie->indirect_info->polymorphic)
    {
      tree t = (VEC_length (tree, known_vals) > (unsigned int) param_index
	        ? VEC_index (tree, known_vals, param_index) : NULL);
      if (t &&
	  TREE_CODE (t) == ADDR_EXPR
	  && TREE_CODE (TREE_OPERAND (t, 0)) == FUNCTION_DECL)
	return TREE_OPERAND (t, 0);
      else
	return NULL_TREE;
    }

  token = ie->indirect_info->otr_token;
  anc_offset = ie->indirect_info->anc_offset;
  otr_type = ie->indirect_info->otr_type;

  t = VEC_index (tree, known_vals, param_index);
  if (!t && known_binfos
      && VEC_length (tree, known_binfos) > (unsigned int) param_index)
    t = VEC_index (tree, known_binfos, param_index);
  if (!t)
    return NULL_TREE;

  if (TREE_CODE (t) != TREE_BINFO)
    {
      tree binfo;
      binfo = gimple_extract_devirt_binfo_from_cst (t);
      if (!binfo)
	return NULL_TREE;
      binfo = get_binfo_at_offset (binfo, anc_offset, otr_type);
      if (!binfo)
	return NULL_TREE;
      return gimple_get_virt_method_for_binfo (token, binfo);
    }
  else
    {
      tree binfo;

      binfo = get_binfo_at_offset (t, anc_offset, otr_type);
      if (!binfo)
	return NULL_TREE;
      return gimple_get_virt_method_for_binfo (token, binfo);
    }
}
