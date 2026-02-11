set_menus_node(void *arg, void *arg2, GtkTreePath *path, int type)
{
	GtkTreeView *tree_view = (GtkTreeView *)arg;
	popup_info_t *popup_win = (popup_info_t *)arg;
	GtkMenu *menu = (GtkMenu *)arg2;
	List button_list = (List)arg2;

	switch(type) {
	case TAB_CLICKED:
		make_fields_menu(NULL, menu, display_data_node, SORTID_CNT);
		break;
	case ROW_CLICKED:
		make_options_menu(tree_view, path, menu, options_data_node);
		break;
	case ROW_LEFT_CLICKED:
	{
		GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
		GtkTreeIter iter;
		if (!gtk_tree_model_get_iter(model, &iter, path)) {
			g_error("error getting iter from model\n");
			break;
		}
		highlight_grid(tree_view, SORTID_POS, (int)NO_VAL, button_list);
		break;
	}
	case FULL_CLICKED:
	{
		GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
		GtkTreeIter iter;
		if (!gtk_tree_model_get_iter(model, &iter, path)) {
			g_error("error getting iter from model\n");
			break;
		}

		popup_all_node(model, &iter, INFO_PAGE);

		break;
	}
	case POPUP_CLICKED:
		make_fields_menu(popup_win, menu,
				 popup_win->display_data, SORTID_CNT);
		break;
	default:
		g_error("UNKNOWN type %d given to set_fields\n", type);
	}
}
