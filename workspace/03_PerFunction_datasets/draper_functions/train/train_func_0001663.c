custom_menu_item_activate_cb (glColorComboMenu *this)
{
        GtkWidget *custom_dialog;
        GtkWidget *colorsel;
        gint       response;
        GdkColor   color;

        gtk_widget_hide (GTK_WIDGET (this));

        custom_dialog = gtk_color_selection_dialog_new (_("Custom Color"));

        colorsel = gtk_color_selection_dialog_get_color_selection (GTK_COLOR_SELECTION_DIALOG (custom_dialog));
        color.red   = GL_COLOR_F_RED   (this->priv->color) * 65535;
        color.green = GL_COLOR_F_GREEN (this->priv->color) * 65535;
        color.blue  = GL_COLOR_F_BLUE  (this->priv->color) * 65535;

        gtk_color_selection_set_current_color (GTK_COLOR_SELECTION (colorsel),
                                               &color);

        response = gtk_dialog_run (GTK_DIALOG (custom_dialog));

        switch (response) {

        case GTK_RESPONSE_OK:
                gtk_color_selection_get_current_color (GTK_COLOR_SELECTION (colorsel),
                                                       &color);
                this->priv->color = GL_COLOR ((color.red   >>8),
                                              (color.green >>8),
                                              (color.blue  >>8));

                gl_color_history_model_add_color (custom_color_history,
                                                  this->priv->color);

                g_signal_emit (this, signals[COLOR_CHANGED], 0,
                               this->priv->color, FALSE);

                gtk_widget_destroy (custom_dialog);
                break;
        default:
                gtk_widget_destroy (custom_dialog);
                break;
        }
}
