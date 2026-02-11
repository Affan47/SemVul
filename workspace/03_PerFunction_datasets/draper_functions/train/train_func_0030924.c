rb_display_page_menu_get_page (RBDisplayPageModel *model, GVariant *parameters)
{
	GtkTreeIter iter;
	void *ptr;

	if (g_variant_is_of_type (parameters, G_VARIANT_TYPE_STRING) == FALSE) {
		rb_debug ("can't find page, variant type is %s", g_variant_get_type_string (parameters));
		return NULL;
	}

	rb_debug ("trying to find page for %s", g_variant_get_string (parameters, NULL));

	if (sscanf (g_variant_get_string (parameters, NULL), "%p", &ptr) != 1) {
		rb_debug ("can't parse parameter");
		return NULL;
	}

	if (rb_display_page_model_find_page_full (model, ptr, &iter) == FALSE) {
		rb_debug ("can't find page matching %p", ptr);
		return NULL;
	}

	return RB_DISPLAY_PAGE (ptr);
}
