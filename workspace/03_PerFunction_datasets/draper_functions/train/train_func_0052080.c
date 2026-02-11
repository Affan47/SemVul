assign_parm_find_data_types (struct assign_parm_data_all *all, tree parm,
			     struct assign_parm_data_one *data)
{
  tree nominal_type, passed_type;
  enum machine_mode nominal_mode, passed_mode, promoted_mode;
  int unsignedp;

  memset (data, 0, sizeof (*data));


  if (!cfun->stdarg)
    data->named_arg = 1;
  else if (DECL_CHAIN (parm))
    data->named_arg = 1;
  else if (targetm.calls.strict_argument_naming (&all->args_so_far))
    data->named_arg = 1;
  else
    data->named_arg = 0;

  nominal_type = TREE_TYPE (parm);
  passed_type = DECL_ARG_TYPE (parm);


  if (TREE_TYPE (parm) == error_mark_node


      || TREE_CODE (parm) != PARM_DECL
      || passed_type == NULL
      || VOID_TYPE_P (nominal_type))
    {
      nominal_type = passed_type = void_type_node;
      nominal_mode = passed_mode = promoted_mode = VOIDmode;
      goto egress;
    }


  passed_mode = TYPE_MODE (passed_type);
  nominal_mode = TYPE_MODE (nominal_type);


  if ((TREE_CODE (passed_type) == UNION_TYPE
       || TREE_CODE (passed_type) == RECORD_TYPE)
      && TYPE_TRANSPARENT_AGGR (passed_type))
    passed_type = TREE_TYPE (first_field (passed_type));


  if (pass_by_reference (&all->args_so_far, passed_mode,
			 passed_type, data->named_arg))
    {
      passed_type = nominal_type = build_pointer_type (passed_type);
      data->passed_pointer = true;
      passed_mode = nominal_mode = Pmode;
    }


  unsignedp = TYPE_UNSIGNED (passed_type);
  promoted_mode = promote_function_mode (passed_type, passed_mode, &unsignedp,
				         TREE_TYPE (current_function_decl), 0);

 egress:
  data->nominal_type = nominal_type;
  data->passed_type = passed_type;
  data->nominal_mode = nominal_mode;
  data->passed_mode = passed_mode;
  data->promoted_mode = promoted_mode;
}
