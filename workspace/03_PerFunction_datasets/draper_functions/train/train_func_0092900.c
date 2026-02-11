cdp_init(MainInfo *min, gchar **name)
{
	P_DirPane	*page = &the_page;

	if(name == NULL)
		return NULL;

	*name = _("Dir Panes");

	page->min   = min;

	init_pane_page(page, 0, _("Right"));
	init_pane_page(page, 1, _("Left"));
	init_paning_page(page);
	init_history_page(page);

	cfg_tree_level_begin(_("Dir Panes"));
	cfg_tree_level_append(_("Left"), page->pane[0].vbox);
	cfg_tree_level_append(_("Right"), page->pane[1].vbox);
	cfg_tree_level_append(_("Pane Split"), page->paning.vbox);
	cfg_tree_level_append(_("History"), page->history.vbox);
	cfg_tree_level_end();
	return NULL;
}
