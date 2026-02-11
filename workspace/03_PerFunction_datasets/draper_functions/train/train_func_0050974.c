unpack_ts_decl_common_value_fields (struct bitpack_d *bp, tree expr)
{
  DECL_MODE (expr) = bp_unpack_enum (bp, machine_mode, MAX_MACHINE_MODE);
  DECL_NONLOCAL (expr) = (unsigned) bp_unpack_value (bp, 1);
  DECL_VIRTUAL_P (expr) = (unsigned) bp_unpack_value (bp, 1);
  DECL_IGNORED_P (expr) = (unsigned) bp_unpack_value (bp, 1);
  DECL_ABSTRACT (expr) = (unsigned) bp_unpack_value (bp, 1);
  DECL_ARTIFICIAL (expr) = (unsigned) bp_unpack_value (bp, 1);
  DECL_USER_ALIGN (expr) = (unsigned) bp_unpack_value (bp, 1);
  DECL_PRESERVE_P (expr) = (unsigned) bp_unpack_value (bp, 1);
  DECL_DEBUG_EXPR_IS_FROM (expr) = (unsigned) bp_unpack_value (bp, 1);
  DECL_EXTERNAL (expr) = (unsigned) bp_unpack_value (bp, 1);
  DECL_GIMPLE_REG_P (expr) = (unsigned) bp_unpack_value (bp, 1);
  DECL_ALIGN (expr) = (unsigned) bp_unpack_var_len_unsigned (bp);

  if (TREE_CODE (expr) == LABEL_DECL)
    {
      DECL_ERROR_ISSUED (expr) = (unsigned) bp_unpack_value (bp, 1);
      EH_LANDING_PAD_NR (expr) = (int) bp_unpack_var_len_unsigned (bp);


      LABEL_DECL_UID (expr) = -1;
    }

  if (TREE_CODE (expr) == FIELD_DECL)
    {
      DECL_PACKED (expr) = (unsigned) bp_unpack_value (bp, 1);
      DECL_NONADDRESSABLE_P (expr) = (unsigned) bp_unpack_value (bp, 1);
      expr->decl_common.off_align = bp_unpack_value (bp, 8);
    }

  if (TREE_CODE (expr) == RESULT_DECL
      || TREE_CODE (expr) == PARM_DECL
      || TREE_CODE (expr) == VAR_DECL)
    {
      DECL_BY_REFERENCE (expr) = (unsigned) bp_unpack_value (bp, 1);
      if (TREE_CODE (expr) == VAR_DECL
	  || TREE_CODE (expr) == PARM_DECL)
	DECL_HAS_VALUE_EXPR_P (expr) = (unsigned) bp_unpack_value (bp, 1);
      DECL_RESTRICTED_P (expr) = (unsigned) bp_unpack_value (bp, 1);
    }
}
