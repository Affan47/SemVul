color_response(GtkWidget *widget, gint response, ColorButton *self) {
    if (response == GTK_RESPONSE_CANCEL) {
	color_button_set_color(self, &self->previous_color);
	color_button_set_alpha(self, self->previous_alpha);
    }
    gtk_widget_destroy(self->dialog);
    self->dialog = NULL;
}
