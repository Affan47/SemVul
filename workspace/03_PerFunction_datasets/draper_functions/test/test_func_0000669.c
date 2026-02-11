object_swap_children (GogObject *a, GogObject *b, char const *name)
{
	GogObjectRole const *role;
	GSList *children_a, *children_b, *ptr;
	GogObject *obj;
	GOStyle *style;
	role = gog_object_find_role_by_name (a, name);
	g_return_if_fail (role);
	children_a = gog_object_get_children (a, role);
	children_b = gog_object_get_children (b, role);
	ptr = children_a;
	while (ptr) {
		obj = GOG_OBJECT (ptr->data);
		style = go_style_dup (
			go_styled_object_get_style (GO_STYLED_OBJECT (obj)));
		gog_object_clear_parent (obj);
		gog_object_add_by_role (b, role, obj);
		go_styled_object_set_style (GO_STYLED_OBJECT (obj), style);
		g_object_unref (style);
		ptr = ptr->next;
	}
	g_slist_free (children_a);
	ptr = children_b;
	while (ptr) {
		obj = GOG_OBJECT (ptr->data);
		style = go_style_dup (
			go_styled_object_get_style (GO_STYLED_OBJECT (obj)));
		gog_object_clear_parent (obj);
		gog_object_add_by_role (a, role, obj);
		go_styled_object_set_style (GO_STYLED_OBJECT (obj), style);
		g_object_unref (style);
		ptr = ptr->next;
	}
	g_slist_free (children_b);
}
