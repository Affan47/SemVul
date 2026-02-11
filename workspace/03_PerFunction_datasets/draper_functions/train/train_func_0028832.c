go_combo_box_popup_hide (GOComboBox *combo_box)
{
	if (!combo_box->priv->torn_off)
		go_combo_box_popup_hide_unconditional (combo_box);
	else if (gtk_widget_get_visible(combo_box->priv->toplevel)) {


		go_combo_popup_tear_off (combo_box, FALSE);
		set_arrow_state (combo_box, FALSE);
	}
}
