panel_menu_get (PanelWidget *panel, PanelData *pd)
{
	if (!pd->menu) {
		pd->menu = panel_context_menu_create (panel);
		if (pd->menu != NULL) {
			g_object_ref_sink (pd->menu);
			g_signal_connect (pd->menu, "deactivate",
					  G_CALLBACK (context_menu_deactivate),
					  pd);
			g_signal_connect (pd->menu, "show",
					  G_CALLBACK (context_menu_show), pd);

			panel_lockdown_on_notify (panel_lockdown_get (),
						  NULL,
						  G_OBJECT (pd->menu),
						  panel_menu_lockdown_changed,
						  pd);
		}
	}

	return pd->menu;
}
