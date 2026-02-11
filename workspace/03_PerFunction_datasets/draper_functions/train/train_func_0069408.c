build_tree (PopplerDocument  *document,
	    GtkTreeModel     *model,
	    GtkTreeIter      *parent,
	    PopplerIndexIter *iter)
{

	do {
		GtkTreeIter       tree_iter;
		PopplerIndexIter *child;
		PopplerAction    *action;
		gboolean          expand;
		gchar            *markup;
		GEnumValue       *enum_value;

		action = poppler_index_iter_get_action (iter);
		expand = poppler_index_iter_is_open (iter);

		if (!action)
			continue;

		markup = g_markup_escape_text (action->any.title, -1);
		enum_value = g_enum_get_value ((GEnumClass *) g_type_class_ref (POPPLER_TYPE_ACTION_TYPE), action->type);

		if (action->type == POPPLER_ACTION_GOTO_DEST &&
		    action->goto_dest.dest->type == POPPLER_DEST_NAMED) {

		}

		gtk_tree_store_append (GTK_TREE_STORE (model), &tree_iter, parent);
		gtk_tree_store_set (GTK_TREE_STORE (model), &tree_iter,
				    OUTLINE_TITLE_COLUMN, markup,
				    OUTLINE_ACTION_TYPE_COLUMN, enum_value->value_name,
				    OUTLINE_EXPAND_COLUMN, expand,
				    OUTLINE_ACTION_COLUMN, action,
				    -1);
		g_object_weak_ref (G_OBJECT (model),
				   (GWeakNotify)poppler_action_free,
				   action);

		g_free (markup);

		child = poppler_index_iter_get_child (iter);
		if (child)
			build_tree (document, model, &tree_iter, child);
		poppler_index_iter_free (child);
	} while (poppler_index_iter_next (iter));
}
