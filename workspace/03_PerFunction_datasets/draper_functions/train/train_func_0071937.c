print_ast_node_c(__isl_take isl_printer *p,
	__isl_keep isl_ast_node *node,
	__isl_keep isl_ast_print_options *options, int in_block, int in_list)
{
	switch (node->type) {
	case isl_ast_node_for:
		if (options->print_for)
			return options->print_for(p,
					isl_ast_print_options_copy(options),
					node, options->print_for_user);
		p = print_for_c(p, node, options, in_block, in_list);
		break;
	case isl_ast_node_if:
		p = print_if_c(p, node, options, 1);
		break;
	case isl_ast_node_block:
		if (!in_block)
			p = start_block(p);
		p = isl_ast_node_list_print(node->u.b.children, p, options);
		if (!in_block)
			p = end_block(p);
		break;
	case isl_ast_node_user:
		if (options->print_user)
			return options->print_user(p,
					isl_ast_print_options_copy(options),
					node, options->print_user_user);
		p = isl_printer_start_line(p);
		p = isl_printer_print_ast_expr(p, node->u.e.expr);
		p = isl_printer_print_str(p, ";");
		p = isl_printer_end_line(p);
		break;
	case isl_ast_node_error:
		break;
	}
	return p;
}
