add_contact_line(struct contact *ec)
{
	GtkTreeIter *sibling = NULL;
	LList *c_iter;
	GtkTreeIter iter;

	if (ec->list_item)
		return;

	ec->pix = iconblank_pb;

	g_free(ec->label);
	ec->label = g_strdup(ec->nick);
	g_free(ec->status);
	ec->status = g_strdup("");

	ec->icon_handler = -1;

	for (c_iter = ec->group->members; c_iter; c_iter = l_list_next(c_iter)) {
		struct contact *c = c_iter->data;
		if (strcasecmp(ec->nick, c->nick) < 0 && c->list_item) {
			sibling = c->list_item;
			break;
		}
	}

	gtk_tree_store_insert_before(contact_list_store, &iter,
		(GtkTreeIter *)ec->group->list_item, sibling);

	gtk_tree_store_set(contact_list_store, &iter,
		MAIN_VIEW_ICON, ec->pix,
		MAIN_VIEW_LABEL, ec->label,
		MAIN_VIEW_STATUS, ec->status,
		MAIN_VIEW_ROW_DATA, ec,
		MAIN_VIEW_ROW_TYPE, TARGET_TYPE_CONTACT,
		MAIN_VIEW_HAS_TIP, TRUE, -1);

	if (ec->list_item)
		gtk_tree_iter_free(ec->list_item);
	ec->list_item = gtk_tree_iter_copy(&iter);

	if (!ec->group->contacts_shown) {
		if (ec->group->list_item
			&& strcmp(_("Unknown"), ec->group->name)
			&& strcmp(_("Ignore"), ec->group->name))

			MAIN_VIEW_EXPAND_ROW(ec->group->list_item);
	}

	ec->group->contacts_shown++;
	ec->expanded ? MAIN_VIEW_EXPAND_ROW(ec->
		list_item) : MAIN_VIEW_COLLAPSE_ROW(ec->list_item);
}
