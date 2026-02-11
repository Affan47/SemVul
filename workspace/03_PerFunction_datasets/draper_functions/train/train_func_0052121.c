get_unary_unsigned(struct bt_list_head *head, uint64_t *value)
{
	struct ctf_node *node;
	int i = 0;

	bt_list_for_each_entry(node, head, siblings) {
		if (node->type != NODE_UNARY_EXPRESSION
				|| node->u.unary_expression.type != UNARY_UNSIGNED_CONSTANT
				|| node->u.unary_expression.link != UNARY_LINK_UNKNOWN
				|| i != 0)
			return -EINVAL;
		*value = node->u.unary_expression.u.unsigned_constant;
		i++;
	}
	return 0;
}
