abraca_cover_art_dialog_get_image (AbracaCoverArtDialog* self) {
	GdkPixbuf* result;
	GtkImage* _tmp0_;
	GdkPixbuf* _tmp1_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->coverart;
	_tmp1_ = gtk_image_get_pixbuf (_tmp0_);
	result = _tmp1_;
	return result;
}
