update_prefs_from_object_page (glPrefsDialog *dialog)
{
	guint     color;
	gboolean  is_default;

	if (dialog->priv->stop_signals) return;

        gl_prefs_model_set_default_font_family (gl_prefs,
                gl_font_combo_get_family (GL_FONT_COMBO (dialog->priv->text_family_combo)));
        gl_prefs_model_set_default_font_size (gl_prefs,
                gtk_spin_button_get_value (GTK_SPIN_BUTTON(dialog->priv->text_size_spin)));

        if (gtk_toggle_button_get_active
            (GTK_TOGGLE_BUTTON (dialog->priv->text_bold_toggle)))
        {
                gl_prefs_model_set_default_font_weight (gl_prefs, PANGO_WEIGHT_BOLD);
        }
        else
        {
                gl_prefs_model_set_default_font_weight (gl_prefs, PANGO_WEIGHT_NORMAL);
        }

        gl_prefs_model_set_default_font_italic_flag (gl_prefs,
                gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON
                                              (dialog->priv->text_italic_toggle)));

        color = gl_color_combo_get_color (GL_COLOR_COMBO(dialog->priv->text_color_combo),
                                          &is_default);
        if (!is_default)
        {
                gl_prefs_model_set_default_text_color (gl_prefs, color);
        }

        if (gtk_toggle_button_get_active
            (GTK_TOGGLE_BUTTON (dialog->priv->text_left_toggle)))
        {
                gl_prefs_model_set_default_text_alignment (gl_prefs, GTK_JUSTIFY_LEFT);
        }
        else if (gtk_toggle_button_get_active
                 (GTK_TOGGLE_BUTTON (dialog->priv->text_right_toggle)))
        {
                gl_prefs_model_set_default_text_alignment (gl_prefs, GTK_JUSTIFY_RIGHT);
        }
        else if (gtk_toggle_button_get_active
                 (GTK_TOGGLE_BUTTON (dialog->priv->text_center_toggle)))
        {
                gl_prefs_model_set_default_text_alignment (gl_prefs, GTK_JUSTIFY_CENTER);
        }
        else
        {

                gl_prefs_model_set_default_text_alignment (gl_prefs, GTK_JUSTIFY_LEFT);
        }


        gl_prefs_model_set_default_text_line_spacing (gl_prefs,
                gtk_spin_button_get_value (GTK_SPIN_BUTTON(dialog->priv->text_line_spacing_spin)));

        gl_prefs_model_set_default_line_width (gl_prefs,
                gtk_spin_button_get_value (GTK_SPIN_BUTTON(dialog->priv->line_width_spin)));

        color = gl_color_combo_get_color (GL_COLOR_COMBO(dialog->priv->line_color_combo),
                                          &is_default);
        if (!is_default)
        {
                gl_prefs_model_set_default_line_color (gl_prefs, color);
        }


        color = gl_color_combo_get_color (GL_COLOR_COMBO(dialog->priv->fill_color_combo),
                                          &is_default);
        if (!is_default)
        {
                gl_prefs_model_set_default_fill_color (gl_prefs, color);
        }
}
