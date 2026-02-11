gl_combo_util_set_strings (GtkComboBoxText   *combo,
                           GList             *list)
{
	GList        *p;

	g_return_if_fail (list);

        gtk_combo_box_text_remove_all (combo);

	for (p=list; p!=NULL; p=p->next) {
		if (p->data) {
			gtk_combo_box_text_append_text (combo, p->data);
		}
	}
}
