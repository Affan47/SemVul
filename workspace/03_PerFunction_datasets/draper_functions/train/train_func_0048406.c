add_field_for_reduction (void **slot, void *data)
{

  struct reduction_info *const red = (struct reduction_info *) *slot;
  tree const type = (tree) data;
  tree var = gimple_assign_lhs (red->reduc_stmt);
  tree field = build_decl (gimple_location (red->reduc_stmt), FIELD_DECL,
			   SSA_NAME_IDENTIFIER (var), TREE_TYPE (var));

  insert_field_into_struct (type, field);

  red->field = field;

  return 1;
}
