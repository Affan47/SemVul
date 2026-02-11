bar_menu_popup(GtkWidget *widget)
{
	GtkWidget *menu;
	GtkWidget *bar;
	GtkWidget *expander;
	const KnownPanes *pane = known_panes;
	BarData *bd;

	bd = g_object_get_data(G_OBJECT(widget), "bar_data");
	if (bd)
		{
		expander = NULL;
		bar = widget;
		}
	else
		{
		expander = widget;
		bar = widget->parent;
		while (bar && !g_object_get_data(G_OBJECT(bar), "bar_data"))
			bar = bar->parent;
		if (!bar) return;
		}

	menu = popup_menu_short_lived();

	if (expander)
		{
		menu_item_add_stock(menu, _("Move to _top"), GTK_STOCK_GOTO_TOP, G_CALLBACK(bar_expander_move_top_cb), expander);
		menu_item_add_stock(menu, _("Move _up"), GTK_STOCK_GO_UP, G_CALLBACK(bar_expander_move_up_cb), expander);
		menu_item_add_stock(menu, _("Move _down"), GTK_STOCK_GO_DOWN, G_CALLBACK(bar_expander_move_down_cb), expander);
		menu_item_add_stock(menu, _("Move to _bottom"), GTK_STOCK_GOTO_BOTTOM, G_CALLBACK(bar_expander_move_bottom_cb), expander);
		menu_item_add_divider(menu);
		menu_item_add_stock(menu, _("Remove"), GTK_STOCK_DELETE, G_CALLBACK(bar_expander_delete_cb), expander);
		menu_item_add_divider(menu);
		}

	while (pane->id)
		{
		GtkWidget *item;
		item = menu_item_add_stock(menu, _(pane->title), GTK_STOCK_ADD, G_CALLBACK(bar_expander_add_cb), bar);
		g_object_set_data(G_OBJECT(item), "pane_add_id", pane->id);
		pane++;
		}

	gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, bar, 0, GDK_CURRENT_TIME);
}
