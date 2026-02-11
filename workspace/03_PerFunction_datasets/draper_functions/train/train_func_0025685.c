dom_element_remove_child (DomElement *self,
			  DomElement *node)
{
	g_return_val_if_fail (DOM_IS_ELEMENT (self), NULL);
	g_return_val_if_fail (DOM_IS_ELEMENT (node), NULL);

	self->child_nodes = g_list_remove (self->child_nodes, node);
	return node;
}
