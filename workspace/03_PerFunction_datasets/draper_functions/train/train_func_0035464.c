mines_start (Mines* self) {
	GtkWindow* _tmp0_ = NULL;
	GtkImage* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->window;
	gtk_widget_show ((GtkWidget*) _tmp0_);
	mines_show_new_game_screen (self);
	_tmp1_ = self->priv->smile_face_image;
	mines_set_face_image (self, _tmp1_);
}
