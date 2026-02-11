compareAndSwapLong_builtin (tree method_return_type ATTRIBUTE_UNUSED,
			    tree orig_call)
{
  enum machine_mode mode = TYPE_MODE (long_type_node);


  if (can_compare_and_swap_p (mode,
			      (flag_use_atomic_builtins
			       && GET_MODE_SIZE (mode) <= UNITS_PER_WORD)))
    {
      tree addr, stmt;
      enum built_in_function fncode = BUILT_IN_SYNC_BOOL_COMPARE_AND_SWAP_8;
      UNMARSHAL5 (orig_call);
      (void) value_type;

      addr = build_addr_sum (long_type_node, obj_arg, offset_arg);
      stmt = build_call_expr (builtin_decl_explicit (fncode),
			      3, addr, expected_arg, value_arg);

      return build_check_this (stmt, this_arg);
    }
  return NULL_TREE;
}
