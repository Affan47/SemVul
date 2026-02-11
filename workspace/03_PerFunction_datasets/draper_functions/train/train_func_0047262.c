__lambda34_ (DocumentTab* self, GtkTextBuffer* s) {
	const gchar* _tmp0_ = NULL;
	Document* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	GtkLabel* _tmp3_ = NULL;
	g_return_if_fail (s != NULL);
	_tmp1_ = self->priv->_document;
	_tmp2_ = document_get_modified (_tmp1_);
	if (_tmp2_) {
		_tmp0_ = "*";
	} else {
		_tmp0_ = "";
	}
	_tmp3_ = self->priv->_label_mark;
	gtk_label_set_label (_tmp3_, _tmp0_);
}
