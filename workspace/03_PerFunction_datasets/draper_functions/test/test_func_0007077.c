cb_preview_clicked (GOComboPixmaps *combo)
{
	gboolean show_arrow;

	if (_go_combo_is_updating (GO_COMBO_BOX (combo)))
		return;

	g_object_get (G_OBJECT (combo), "show-arrow", &show_arrow, NULL);
	if (show_arrow)
		emit_change (combo);
	else {

		go_combo_box_popup_display (GO_COMBO_BOX (combo));
	}
}
