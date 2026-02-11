aapcs_vfp_is_call_or_return_candidate (enum arm_pcs pcs_variant,
				       enum machine_mode mode, const_tree type,
				       enum machine_mode *base_mode, int *count)
{
  enum machine_mode new_mode = VOIDmode;


  if (type)
    {
      int ag_count = aapcs_vfp_sub_candidate (type, &new_mode);

      if (ag_count > 0 && ag_count <= 4)
	*count = ag_count;
      else
	return false;
    }
  else if (GET_MODE_CLASS (mode) == MODE_FLOAT
	   || GET_MODE_CLASS (mode) == MODE_VECTOR_INT
	   || GET_MODE_CLASS (mode) == MODE_VECTOR_FLOAT)
    {
      *count = 1;
      new_mode = mode;
    }
  else if (GET_MODE_CLASS (mode) == MODE_COMPLEX_FLOAT)
    {
      *count = 2;
      new_mode = (mode == DCmode ? DFmode : SFmode);
    }
  else
    return false;


  if (!use_vfp_abi (pcs_variant, ARM_NUM_REGS (new_mode) > 1))
    return false;

  *base_mode = new_mode;
  return true;
}
