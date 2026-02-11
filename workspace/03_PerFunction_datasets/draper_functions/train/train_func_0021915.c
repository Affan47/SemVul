open_file(GtkWidget *widget, gchar *data)
{
	gchar *t;
 	if(imodif == DATA_MOD_YES)
        {
		t = g_strdup_printf(_("\nThe \"%s\" file has been modified.\n\n"),get_name_file(fileopen.datafile));
		t = g_strdup_printf(_(" %sIf you continue, you lose what you have changed.\n\n"),t);
		t = g_strdup_printf(_(" %sYou want to continue?\n"),t);
		Continue_YesNo(charge_doc, NULL,t);
		g_free(t);
        }
        else
        {
		charge_doc(NULL, NULL);
 		data_modify(FALSE);
 	}
}
