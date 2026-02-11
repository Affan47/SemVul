node_merge_block(struct grecs_node *to_node, struct grecs_node *from_node,
		 struct grecs_keyword *kwp)
{
	struct grecs_node *sp;

	if (!from_node->down)
		return;
	for (sp = from_node->down; ; sp = sp->next) {
		sp->up = to_node;
		if (!sp->next)
			break;
	}
	sp->next = to_node->down;
	to_node->down = from_node->down;
	from_node->down = NULL;
}
