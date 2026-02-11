objstack_destroy(struct objstack *objstack)
{
	struct objstack_node *node, *p;

	if (!objstack)
		return;
	bt_list_for_each_entry_safe(node, p, &objstack->head, node) {
		bt_list_del(&node->node);
		objstack_node_free(node);
	}
	free(objstack);
}
