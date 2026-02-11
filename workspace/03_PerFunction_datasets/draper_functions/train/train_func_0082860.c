tree_iterator__pop_frame(tree_iterator *ti)
{
	tree_iterator_frame *tf = ti->stack;
	ti->stack = tf->next;
	if (ti->stack != NULL) {
		git_tree_free(tf->tree);
		ti->stack->prev = NULL;
	}
	git__free(tf);
}
