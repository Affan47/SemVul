compute_uninit_opnds_pos (gimple phi)
{
  size_t i, n;
  unsigned uninit_opnds = 0;

  n = gimple_phi_num_args (phi);

  if (n > 32)
    return 0;

  for (i = 0; i < n; ++i)
    {
      tree op = gimple_phi_arg_def (phi, i);
      if (TREE_CODE (op) == SSA_NAME
          && uninit_undefined_value_p (op)
          && !can_skip_redundant_opnd (op, phi))
        MASK_SET_BIT (uninit_opnds, i);
    }
  return uninit_opnds;
}
