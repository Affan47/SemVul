___lambda45_ (Block11Data* _data11_, GtkButton* source) {
	Block7Data* _data7_;
	GmpcBrowsersMetadata * self;
	gint _tmp0_;
	GtkNotebook* _tmp1_;
	gint _tmp2_;
	GmpcMetaDataWidgetsSimilarArtists* _tmp3_;
	_data7_ = _data11_->_data7_;
	self = _data7_->self;
	g_return_if_fail (source != NULL);
	_tmp0_ = _data11_->j;
	g_debug ("gmpc-metadata-browser2.vala:1257: notebook page %i clicked", _tmp0_);
	_tmp1_ = _data7_->notebook;
	_tmp2_ = _data11_->j;
	gtk_notebook_set_current_page (_tmp1_, _tmp2_);
	_tmp3_ = _data11_->similar_artist;
	gmpc_meta_data_widgets_similar_artists_first_show (_tmp3_);
}
