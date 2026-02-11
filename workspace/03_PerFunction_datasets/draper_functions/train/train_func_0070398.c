ccss_stylesheet_unload (ccss_stylesheet_t	*self,
			unsigned int		 descriptor)
{
	ccss_selector_group_t	*group;
	GHashTableIter		 iter;
	bool			 ret;

	g_return_val_if_fail (self, false);

	ret = false;
	g_hash_table_iter_init (&iter, self->groups);
	while (g_hash_table_iter_next (&iter, NULL, (gpointer *) &group)) {
		ret |= ccss_selector_group_unload (group, descriptor);
	}

	return ret;
}
