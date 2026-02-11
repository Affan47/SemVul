build_input_checkbox(CmdDlg *dlg, const gchar *label, const gchar *def, CmdInp *inp)
{
	if(def != NULL)
	{
		inp->type = CITP_CHECKBOX;
		inp->inp.checkbox.check = gtk_check_button_new_with_label(label);
		inp->inp.checkbox.active   = the_true;
		inp->inp.checkbox.inactive = the_false;

		if(*def == '*')
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(inp->inp.checkbox.check), TRUE);
			def++;
		}
		if(*def == '=')
		{
			def = stu_scan_string(++def, (const gchar **) &inp->inp.checkbox.active);
			if(*def == ',')
				stu_scan_string(++def, (const gchar **) &inp->inp.checkbox.inactive);
		}
		pack_input_widget(dlg, inp->inp.checkbox.check, 1, 0);
	}
	return def != NULL;
}
