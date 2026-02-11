lto_input_tree_pointers (struct lto_input_block *ib, struct data_in *data_in,
			 tree expr)
{
  enum tree_code code;

  code = TREE_CODE (expr);

  if (CODE_CONTAINS_STRUCT (code, TS_COMMON))
    lto_input_ts_common_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_VECTOR))
    lto_input_ts_vector_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_COMPLEX))
    lto_input_ts_complex_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_DECL_MINIMAL))
    lto_input_ts_decl_minimal_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_DECL_COMMON))
    lto_input_ts_decl_common_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_DECL_NON_COMMON))
    lto_input_ts_decl_non_common_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_DECL_WITH_VIS))
    lto_input_ts_decl_with_vis_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_FIELD_DECL))
    lto_input_ts_field_decl_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_FUNCTION_DECL))
    lto_input_ts_function_decl_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_TYPE))
    lto_input_ts_type_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_LIST))
    lto_input_ts_list_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_VEC))
    lto_input_ts_vec_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_EXP))
    lto_input_ts_exp_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_SSA_NAME))
    {

      gcc_unreachable ();
    }

  if (CODE_CONTAINS_STRUCT (code, TS_BLOCK))
    lto_input_ts_block_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_BINFO))
    lto_input_ts_binfo_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_STATEMENT_LIST))
    {

      gcc_unreachable ();
    }

  if (CODE_CONTAINS_STRUCT (code, TS_CONSTRUCTOR))
    lto_input_ts_constructor_tree_pointers (ib, data_in, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_OMP_CLAUSE))
    {

      gcc_unreachable ();
    }

  if (CODE_CONTAINS_STRUCT (code, TS_OPTIMIZATION))
    {
      sorry ("optimization options not supported yet");
    }

  if (CODE_CONTAINS_STRUCT (code, TS_TARGET_OPTION))
    lto_input_ts_target_option (ib, expr);

  if (CODE_CONTAINS_STRUCT (code, TS_TRANSLATION_UNIT_DECL))
    lto_input_ts_translation_unit_decl_tree_pointers (ib, data_in, expr);
}
