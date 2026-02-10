update_theme_from_controls (GthContactSheetThemeDialog *self)
{
	self->priv->theme->display_name = g_strdup (gtk_entry_get_text (GTK_ENTRY (GET_WIDGET ("name_entry"))));


	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (GET_WIDGET ("solid_color_radiobutton")))) {
		self->priv->theme->background_type = GTH_CONTACT_SHEET_BACKGROUND_TYPE_SOLID;
		gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (GET_WIDGET ("solid_color_colorpicker")), &self->priv->theme->background_color1);
	}
	else {
		gboolean h_gradient_active = FALSE;
		gboolean v_gradient_active = FALSE;

		h_gradient_active = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (GET_WIDGET ("h_gradient_checkbutton")));
		v_gradient_active = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (GET_WIDGET ("v_gradient_checkbutton")));

		if (h_gradient_active && v_gradient_active) {
			self->priv->theme->background_type = GTH_CONTACT_SHEET_BACKGROUND_TYPE_FULL;
			gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (GET_WIDGET ("h_gradient_1_colorpicker")), &self->priv->theme->background_color1);
			gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (GET_WIDGET ("h_gradient_2_colorpicker")), &self->priv->theme->background_color2);
			gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (GET_WIDGET ("v_gradient_1_colorpicker")), &self->priv->theme->background_color3);
			gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (GET_WIDGET ("v_gradient_2_colorpicker")), &self->priv->theme->background_color4);
		}
		else if (h_gradient_active) {
			self->priv->theme->background_type = GTH_CONTACT_SHEET_BACKGROUND_TYPE_HORIZONTAL;
			gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (GET_WIDGET ("h_gradient_1_colorpicker")), &self->priv->theme->background_color1);
			gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (GET_WIDGET ("h_gradient_2_colorpicker")), &self->priv->theme->background_color2);
		}
		else if (v_gradient_active) {
			self->priv->theme->background_type = GTH_CONTACT_SHEET_BACKGROUND_TYPE_VERTICAL;
			gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (GET_WIDGET ("v_gradient_1_colorpicker")), &self->priv->theme->background_color1);
			gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (GET_WIDGET ("v_gradient_2_colorpicker")), &self->priv->theme->background_color2);
		}
	}


	self->priv->theme->frame_style = gtk_combo_box_get_active (GTK_COMBO_BOX (GET_WIDGET ("frame_style_combobox")));
	gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (GET_WIDGET ("frame_colorpicker")), &self->priv->theme->frame_color);


	self->priv->theme->header_font_name = g_strdup (gtk_font_button_get_font_name (GTK_FONT_BUTTON (GET_WIDGET ("header_fontpicker"))));
	gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (GET_WIDGET ("header_colorpicker")), &self->priv->theme->header_color);


	self->priv->theme->footer_font_name = g_strdup (gtk_font_button_get_font_name (GTK_FONT_BUTTON (GET_WIDGET ("footer_fontpicker"))));
	gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (GET_WIDGET ("footer_colorpicker")), &self->priv->theme->footer_color);


	self->priv->theme->caption_font_name = g_strdup (gtk_font_button_get_font_name (GTK_FONT_BUTTON (GET_WIDGET ("caption_fontpicker"))));
	gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (GET_WIDGET ("caption_colorpicker")), &self->priv->theme->caption_color);
}
