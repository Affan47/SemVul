gphpedit_status_combo_box_set_item_text (GphpeditStatusComboBox *combo,
				      GtkMenuItem	  *item,
				      const gchar         *text)
{
	g_return_if_fail (GPHPEDIT_IS_STATUS_COMBO_BOX (combo));
	g_return_if_fail (GTK_IS_MENU_ITEM (item));

	g_object_set_data_full (G_OBJECT (item),
				COMBO_BOX_TEXT_DATA,
				g_strdup (text),
				(GDestroyNotify)g_free);
}
