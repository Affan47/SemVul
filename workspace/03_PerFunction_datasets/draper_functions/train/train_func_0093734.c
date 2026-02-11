write_member_name (tree member)
{
  if (TREE_CODE (member) == IDENTIFIER_NODE)
    write_unqualified_id (member);
  else if (DECL_P (member))
    write_unqualified_name (member);
  else if (TREE_CODE (member) == TEMPLATE_ID_EXPR)
    {
      tree name = TREE_OPERAND (member, 0);
      if (TREE_CODE (name) == OVERLOAD)
	name = OVL_FUNCTION (name);
      write_member_name (name);
      write_template_args (TREE_OPERAND (member, 1));
    }
  else
    write_expression (member);
}
