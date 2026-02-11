update_sensitivity(void)
{
	gtk_widget_set_sensitive(personeditdlg.entry_name,    !personeditdlg.read_only);
	gtk_widget_set_sensitive(personeditdlg.entry_first,   !personeditdlg.read_only);
	gtk_widget_set_sensitive(personeditdlg.entry_last,    !personeditdlg.read_only);
	gtk_widget_set_sensitive(personeditdlg.entry_nick,    !personeditdlg.read_only && !personeditdlg.ldap);
	gtk_widget_set_sensitive(personeditdlg.entry_email,   !personeditdlg.read_only);
	gtk_widget_set_sensitive(personeditdlg.entry_alias,   !personeditdlg.read_only && !personeditdlg.ldap);
	gtk_widget_set_sensitive(personeditdlg.entry_remarks, !personeditdlg.read_only && !personeditdlg.ldap);
	gtk_widget_set_sensitive(personeditdlg.email_up,      !personeditdlg.read_only);
	gtk_widget_set_sensitive(personeditdlg.email_down,    !personeditdlg.read_only);
	gtk_widget_set_sensitive(personeditdlg.email_del,     !personeditdlg.read_only);
	gtk_widget_set_sensitive(personeditdlg.email_mod,     !personeditdlg.read_only);
	gtk_widget_set_sensitive(personeditdlg.email_add,     !personeditdlg.read_only);
	gtk_widget_set_sensitive(personeditdlg.entry_atname,  !personeditdlg.read_only);
	gtk_widget_set_sensitive(personeditdlg.entry_atvalue, !personeditdlg.read_only);
	gtk_widget_set_sensitive(personeditdlg.attrib_add,    !personeditdlg.read_only);
	gtk_widget_set_sensitive(personeditdlg.attrib_del,    !personeditdlg.read_only);
	gtk_widget_set_sensitive(personeditdlg.attrib_mod,    !personeditdlg.read_only);
}
