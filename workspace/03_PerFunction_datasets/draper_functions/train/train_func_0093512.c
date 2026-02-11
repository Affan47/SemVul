unregister_child (SeahorseObject* self, SeahorseObject* child)
{
	g_assert (SEAHORSE_IS_OBJECT (self));
	g_assert (SEAHORSE_IS_OBJECT (child));
	g_assert (self != child);
	g_assert (child->pv->parent == self);

	child->pv->parent = NULL;
	self->pv->children = g_list_remove (self->pv->children, child);
}
