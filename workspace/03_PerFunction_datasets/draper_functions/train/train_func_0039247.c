add_stmt_with_node (tree gnu_stmt, Node_Id gnat_node)
{
  if (Present (gnat_node))
    set_expr_location_from_node (gnu_stmt, gnat_node);
  add_stmt (gnu_stmt);
}
