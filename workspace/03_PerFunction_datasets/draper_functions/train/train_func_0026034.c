set_menus_submit(void *arg, void *arg2,
			     GtkTreePath *path, int type)
{
	GtkTreeView *tree_view = (GtkTreeView *)arg;
	popup_info_t *popup_win = (popup_info_t *)arg;
	GtkMenu *menu = (GtkMenu *)arg2;


	switch(type) {
	case TAB_CLICKED:
		make_fields_menu(NULL, menu, display_data_submit, SORTID_CNT);
		break;
	case ROW_CLICKED:
		make_options_menu(tree_view, path, menu, options_data_submit);
		break;
	case POPUP_CLICKED:
		make_fields_menu(popup_win, menu,
				 popup_win->display_data, SORTID_CNT);
		break;
	default:
		g_error("UNKNOWN type %d given to set_fields\n", type);
	}
}
