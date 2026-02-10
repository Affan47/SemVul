panel_struts_find_strut (PanelToplevel *toplevel)
{
	GSList *l;

	for (l = panel_struts_list; l; l = l->next) {
		PanelStrut *strut = l->data;

		if (strut->toplevel == toplevel)
			break;
	}

	return l ? l->data : NULL;
}
