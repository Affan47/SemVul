key_press_callback (GtkWidget *widget, GdkEventKey *event, gpointer callback_data)
{
	NautilusView *view;
	GdkEventButton button_event = { 0 };
	gboolean handled;
	GtkTreeView *tree_view;
	GtkTreePath *path;

	tree_view = GTK_TREE_VIEW (widget);

	view = NAUTILUS_VIEW (callback_data);
	handled = FALSE;

	switch (event->keyval) {
	case GDK_KEY_F10:
		if (event->state & GDK_CONTROL_MASK) {
			nautilus_view_pop_up_background_context_menu (view, &button_event);
			handled = TRUE;
		}
		break;
	case GDK_KEY_Right:
		gtk_tree_view_get_cursor (tree_view, &path, NULL);
		if (path) {
			gtk_tree_view_expand_row (tree_view, path, FALSE);
			gtk_tree_path_free (path);
		}
		handled = TRUE;
		break;
	case GDK_KEY_Left:
		gtk_tree_view_get_cursor (tree_view, &path, NULL);
		if (path) {
			if (!gtk_tree_view_collapse_row (tree_view, path)) {


				if ((gtk_tree_path_get_depth (path) > 1) && gtk_tree_path_up (path)) {
					gtk_tree_view_set_cursor (tree_view, path, NULL, FALSE);
				}
			}

			gtk_tree_path_free (path);
		}
		handled = TRUE;
		break;
	case GDK_KEY_space:
		if (event->state & GDK_CONTROL_MASK) {
			handled = FALSE;
			break;
		}
		if (!gtk_widget_has_focus (GTK_WIDGET (NAUTILUS_LIST_VIEW (view)->details->tree_view))) {
			handled = FALSE;
			break;
		}
		if ((event->state & GDK_SHIFT_MASK) != 0) {
			activate_selected_items_alternate (NAUTILUS_LIST_VIEW (view), NULL, TRUE);
		} else {
			preview_selected_items (NAUTILUS_LIST_VIEW (view));
		}
		handled = TRUE;
		break;
	case GDK_KEY_Return:
	case GDK_KEY_KP_Enter:
		if ((event->state & GDK_SHIFT_MASK) != 0) {
			activate_selected_items_alternate (NAUTILUS_LIST_VIEW (view), NULL, TRUE);
		} else {
			activate_selected_items (NAUTILUS_LIST_VIEW (view));
		}
		handled = TRUE;
		break;
	case GDK_KEY_v:

		if ((event->state & GDK_CONTROL_MASK) != 0) {
			handled = TRUE;
		}
		break;

	default:
		handled = FALSE;
	}

	return handled;
}
