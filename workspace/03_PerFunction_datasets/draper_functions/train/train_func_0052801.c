dupe_listview_press_cb(GtkWidget *widget, GdkEventButton *bevent, gpointer data)
{
	DupeWindow *dw = data;
	GtkTreeModel *store;
	GtkTreePath *tpath;
	GtkTreeIter iter;
	DupeItem *di = NULL;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(widget));

	if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(widget), bevent->x, bevent->y,
					  &tpath, NULL, NULL, NULL))
		{
		gtk_tree_model_get_iter(store, &iter, tpath);
		gtk_tree_model_get(store, &iter, DUPE_COLUMN_POINTER, &di, -1);
		gtk_tree_path_free(tpath);
		}

	dw->click_item = di;

	if (bevent->button == MOUSE_BUTTON_RIGHT)
		{

		GtkWidget *menu;

		if (bevent->state & GDK_CONTROL_MASK && bevent->state & GDK_SHIFT_MASK)
			{
			dupe_display_stats(dw, di);
			return TRUE;
			}
		if (widget == dw->listview)
			{
			menu = dupe_menu_popup_main(dw, di);
			}
		else
			{
			menu = dupe_menu_popup_second(dw, di);
			}
		gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, bevent->button, bevent->time);
		}

	if (!di) return FALSE;

	if (bevent->button == MOUSE_BUTTON_LEFT &&
	    bevent->type == GDK_2BUTTON_PRESS)
		{
		dupe_menu_view(dw, di, widget, FALSE);
		}

	if (bevent->button == MOUSE_BUTTON_MIDDLE) return TRUE;

	if (bevent->button == MOUSE_BUTTON_RIGHT)
		{
		if (!dupe_listview_item_is_selected(dw, di, widget))
			{
			GtkTreeSelection *selection;

			selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(widget));
			gtk_tree_selection_unselect_all(selection);
			gtk_tree_selection_select_iter(selection, &iter);

			tpath = gtk_tree_model_get_path(GTK_TREE_MODEL(store), &iter);
			gtk_tree_view_set_cursor(GTK_TREE_VIEW(widget), tpath, NULL, FALSE);
			gtk_tree_path_free(tpath);
			}

		return TRUE;
		}

	if (bevent->button == MOUSE_BUTTON_LEFT &&
	    bevent->type == GDK_BUTTON_PRESS &&
	    !(bevent->state & GDK_SHIFT_MASK ) &&
	    !(bevent->state & GDK_CONTROL_MASK ) &&
	    dupe_listview_item_is_selected(dw, di, widget))
		{

		gtk_widget_grab_focus(widget);
		return TRUE;
		}

	return FALSE;
}
