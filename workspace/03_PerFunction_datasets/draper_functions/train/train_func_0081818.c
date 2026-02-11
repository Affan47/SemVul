e_contact_pretty_name (EContactField field_id)
{
	g_return_val_if_fail (field_id >= 1 && field_id < E_CONTACT_FIELD_LAST, "");

#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
#endif

	return _(field_info[field_id].pretty_name);
}
