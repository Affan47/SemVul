print_arg_this_expr(int lvl, struct string *str, struct expression *expr)
{
	int err;

	err = append_formatted(lvl, str, "ARG_THIS:\n");
	if (err)
		goto out;

	err = append_tree_attr(lvl + 1, str, "arg_expression",
			       expr->arg_expression);

out:
	return err;
}
