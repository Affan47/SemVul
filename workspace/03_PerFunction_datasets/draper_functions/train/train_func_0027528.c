_gdata_app_categories_add_category (GDataAPPCategories *self, GDataCategory *category)
{
	g_return_if_fail (GDATA_IS_APP_CATEGORIES (self));
	g_return_if_fail (GDATA_IS_CATEGORY (category));


	if (gdata_category_get_scheme (category) == NULL)
		gdata_category_set_scheme (category, self->priv->scheme);

	self->priv->categories = g_list_prepend (self->priv->categories, g_object_ref (category));
}
