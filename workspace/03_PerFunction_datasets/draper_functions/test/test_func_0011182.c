_set_active_combo_defaults(GtkComboBox *combo,
				       sview_config_t *sview_config,
				       int type)
{
	int action = 0;

	switch(type) {
	case SORTID_ADMIN:
		action = sview_config->admin_mode;
		break;
	case SORTID_GRID_TOPO_ORDER:
		action = sview_config->grid_topological;
		break;
	case SORTID_RULED_TV:
		action = sview_config->ruled_treeview;
		break;
	case SORTID_SHOW_GRID:
		action = sview_config->show_grid;
		break;
	case SORTID_SHOW_HIDDEN:
		action = sview_config->show_hidden;
		break;
	case SORTID_SAVE_PAGE_OPTS:
		action = sview_config->save_page_opts;
		break;
	case SORTID_DEFAULT_PAGE:
		action = sview_config->default_page;
		break;
	case SORTID_TAB_POS:
		action = _trans_tab_pos(sview_config->tab_pos);
		break;
	default:
		break;
	}

	gtk_combo_box_set_active(combo, action);
}
