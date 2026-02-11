context_menu_deactivate (GtkWidget *w,
			 PanelData *pd)
{
	if (pd->deactivate_idle == 0)
		pd->deactivate_idle = g_idle_add (deactivate_idle, pd);

	panel_toplevel_pop_autohide_disabler (PANEL_TOPLEVEL (pd->panel));
}
