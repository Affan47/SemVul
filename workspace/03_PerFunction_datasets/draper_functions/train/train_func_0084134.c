df_ref_create_structure (enum df_ref_class cl,
			 struct df_collection_rec *collection_rec,
			 rtx reg, rtx *loc,
			 basic_block bb, struct df_insn_info *info,
			 enum df_ref_type ref_type,
			 int ref_flags)
{
  df_ref this_ref = NULL;
  int regno = REGNO (GET_CODE (reg) == SUBREG ? SUBREG_REG (reg) : reg);
  struct df_scan_problem_data *problem_data
    = (struct df_scan_problem_data *) df_scan->problem_data;

  switch (cl)
    {
    case DF_REF_BASE:
      this_ref = (df_ref) pool_alloc (problem_data->ref_base_pool);
      gcc_checking_assert (loc == NULL);
      break;

    case DF_REF_ARTIFICIAL:
      this_ref = (df_ref) pool_alloc (problem_data->ref_artificial_pool);
      this_ref->artificial_ref.bb = bb;
      gcc_checking_assert (loc == NULL);
      break;

    case DF_REF_REGULAR:
      this_ref = (df_ref) pool_alloc (problem_data->ref_regular_pool);
      this_ref->regular_ref.loc = loc;
      gcc_checking_assert (loc);
      break;
    }

  DF_REF_CLASS (this_ref) = cl;
  DF_REF_ID (this_ref) = -1;
  DF_REF_REG (this_ref) = reg;
  DF_REF_REGNO (this_ref) =  regno;
  DF_REF_TYPE (this_ref) = ref_type;
  DF_REF_INSN_INFO (this_ref) = info;
  DF_REF_CHAIN (this_ref) = NULL;
  DF_REF_FLAGS (this_ref) = ref_flags;
  DF_REF_NEXT_REG (this_ref) = NULL;
  DF_REF_PREV_REG (this_ref) = NULL;
  DF_REF_ORDER (this_ref) = df->ref_order++;


  DF_REF_FLAGS_CLEAR (this_ref, DF_HARD_REG_LIVE);


  if ((regno < FIRST_PSEUDO_REGISTER)
      && (!DF_REF_IS_ARTIFICIAL (this_ref)))
    {
      if (DF_REF_REG_DEF_P (this_ref))
	{
	  if (!DF_REF_FLAGS_IS_SET (this_ref, DF_REF_MAY_CLOBBER))
	    DF_REF_FLAGS_SET (this_ref, DF_HARD_REG_LIVE);
	}
      else if (!(TEST_HARD_REG_BIT (elim_reg_set, regno)
		 && (regno == FRAME_POINTER_REGNUM
		     || regno == ARG_POINTER_REGNUM)))
	DF_REF_FLAGS_SET (this_ref, DF_HARD_REG_LIVE);
    }

  if (collection_rec)
    {
      if (DF_REF_REG_DEF_P (this_ref))
	VEC_safe_push (df_ref, stack, collection_rec->def_vec, this_ref);
      else if (DF_REF_FLAGS (this_ref) & DF_REF_IN_NOTE)
	VEC_safe_push (df_ref, stack, collection_rec->eq_use_vec, this_ref);
      else
	VEC_safe_push (df_ref, stack, collection_rec->use_vec, this_ref);
    }
  else
    df_install_ref_incremental (this_ref);

  return this_ref;
}
