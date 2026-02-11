boxes_searchbar_refilter (BoxesSearchbar* self) {
	gboolean result = FALSE;
	BoxesApp* _tmp0_ = NULL;
	BoxesCollectionFilter* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	BoxesApp* _tmp4_ = NULL;
	BoxesCollectionView* _tmp5_ = NULL;
#line 38 "/extra-data/checkout/gnome/gnome-boxes/src/searchbar.vala"
	g_return_val_if_fail (self != NULL, FALSE);
#line 39 "/extra-data/checkout/gnome/gnome-boxes/src/searchbar.vala"
	_tmp0_ = boxes_app_app;
#line 39 "/extra-data/checkout/gnome/gnome-boxes/src/searchbar.vala"
	_tmp1_ = _tmp0_->filter;
#line 39 "/extra-data/checkout/gnome/gnome-boxes/src/searchbar.vala"
	_tmp2_ = boxes_searchbar_get_text (self);
#line 39 "/extra-data/checkout/gnome/gnome-boxes/src/searchbar.vala"
	_tmp3_ = _tmp2_;
#line 39 "/extra-data/checkout/gnome/gnome-boxes/src/searchbar.vala"
	boxes_collection_filter_set_text (_tmp1_, _tmp3_);
#line 40 "/extra-data/checkout/gnome/gnome-boxes/src/searchbar.vala"
	_tmp4_ = boxes_app_app;
#line 40 "/extra-data/checkout/gnome/gnome-boxes/src/searchbar.vala"
	_tmp5_ = _tmp4_->view;
#line 40 "/extra-data/checkout/gnome/gnome-boxes/src/searchbar.vala"
	boxes_collection_view_refilter (_tmp5_);
#line 41 "/extra-data/checkout/gnome/gnome-boxes/src/searchbar.vala"
	self->priv->refilter_delay_id = (guint) 0;
#line 43 "/extra-data/checkout/gnome/gnome-boxes/src/searchbar.vala"
	result = FALSE;
#line 43 "/extra-data/checkout/gnome/gnome-boxes/src/searchbar.vala"
	return result;
#line 492 "searchbar.c"
}
