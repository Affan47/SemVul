gog_object_get_children (GogObject const *obj, GogObjectRole const *filter)
{
	GSList *ptr, *res = NULL;

	g_return_val_if_fail (GOG_IS_OBJECT (obj), NULL);

	if (filter == NULL)
		return g_slist_copy (obj->children);

	for (ptr = obj->children ; ptr != NULL ; ptr = ptr->next)
		if (GOG_OBJECT (ptr->data)->role == filter)
			res = g_slist_prepend (res, ptr->data);
	return g_slist_reverse (res);
}
