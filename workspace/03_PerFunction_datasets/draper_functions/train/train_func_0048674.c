eval_and_append_input(CmdDlg *dlg, gint row, GString *out)
{
	GList	*data;
	gchar	*tmp;

	if(row >= 0 && row < dlg->row)
	{
		switch(dlg->input[row].type)
		{
			case CITP_STRING:
				g_string_append(out, gtk_entry_get_text(GTK_ENTRY(dlg->input[row].inp.string.entry)));
				return TRUE;
			case CITP_MENU:
				if((data = g_list_nth(dlg->input[row].inp.menu.items, dlg->input[row].inp.menu.current)) != NULL)
				{
					gchar	*colon;

					if((colon = strchr(data->data, ':')) != NULL)
						g_string_append(out, colon + 1);
					else
						g_string_append(out, data->data);
					return TRUE;
				}
				return FALSE;
			case CITP_COMBO:
				tmp = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(dlg->input[row].inp.combo.combo));
				g_string_append(out, tmp);
				return TRUE;
			case CITP_CHECKBOX:
				if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(dlg->input[row].inp.checkbox.check)))
					g_string_append(out, dlg->input[row].inp.checkbox.active);
				else
					g_string_append(out, dlg->input[row].inp.checkbox.inactive);
				return TRUE;
			case CITP_LABEL:
				return TRUE;
		}
	}
	return FALSE;
}
