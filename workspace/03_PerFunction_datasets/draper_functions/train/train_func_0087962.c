visit_phi (gimple phi)
{
  bool changed = false;
  tree result;
  tree sameval = VN_TOP;
  bool allsame = true;
  unsigned i;


  if (SSA_NAME_OCCURS_IN_ABNORMAL_PHI (PHI_RESULT (phi)))
    return set_ssa_val_to (PHI_RESULT (phi), PHI_RESULT (phi));


  for (i = 0; i < gimple_phi_num_args (phi); i++)
    {
      tree def = PHI_ARG_DEF (phi, i);

      if (TREE_CODE (def) == SSA_NAME)
	def = SSA_VAL (def);
      if (def == VN_TOP)
	continue;
      if (sameval == VN_TOP)
	{
	  sameval = def;
	}
      else
	{
	  if (!expressions_equal_p (def, sameval))
	    {
	      allsame = false;
	      break;
	    }
	}
    }


  if (allsame)
    {
      if (is_gimple_min_invariant (sameval))
	{
	  VN_INFO (PHI_RESULT (phi))->has_constants = true;
	  VN_INFO (PHI_RESULT (phi))->expr = sameval;
	}
      else
	{
	  VN_INFO (PHI_RESULT (phi))->has_constants = false;
	  VN_INFO (PHI_RESULT (phi))->expr = sameval;
	}

      if (TREE_CODE (sameval) == SSA_NAME)
	return visit_copy (PHI_RESULT (phi), sameval);

      return set_ssa_val_to (PHI_RESULT (phi), sameval);
    }


  result = vn_phi_lookup (phi);
  if (result)
    {
      if (TREE_CODE (result) == SSA_NAME)
	changed = visit_copy (PHI_RESULT (phi), result);
      else
	changed = set_ssa_val_to (PHI_RESULT (phi), result);
    }
  else
    {
      vn_phi_insert (phi, PHI_RESULT (phi));
      VN_INFO (PHI_RESULT (phi))->has_constants = false;
      VN_INFO (PHI_RESULT (phi))->expr = PHI_RESULT (phi);
      changed = set_ssa_val_to (PHI_RESULT (phi), PHI_RESULT (phi));
    }

  return changed;
}
