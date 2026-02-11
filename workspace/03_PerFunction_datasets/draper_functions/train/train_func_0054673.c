boxes_collection_view_get_item_pos (BoxesCollectionView* self, BoxesCollectionItem* item, gfloat* x, gfloat* y) {
	gfloat _vala_x = 0.0F;
	gfloat _vala_y = 0.0F;
	GdkRectangle rect = {0};
	GtkTreePath* path = NULL;
	BoxesCollectionItem* _tmp0_ = NULL;
	GtkTreePath* _tmp1_ = NULL;
	GtkTreePath* _tmp2_ = NULL;
#line 52 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
	g_return_if_fail (self != NULL);
#line 52 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
	g_return_if_fail (item != NULL);
#line 54 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
	_tmp0_ = item;
#line 54 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
	_tmp1_ = boxes_collection_view_get_path_for_item (self, _tmp0_);
#line 54 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
	path = _tmp1_;
#line 55 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
	_tmp2_ = path;
#line 55 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
	if (_tmp2_ != NULL) {
#line 693 "collection-view.c"
		GdMainView* _tmp3_ = NULL;
		GtkWidget* _tmp4_ = NULL;
		GtkTreePath* _tmp5_ = NULL;
		GdkRectangle _tmp6_ = {0};
		GdkRectangle _tmp7_ = {0};
		gint _tmp8_ = 0;
		GdkRectangle _tmp9_ = {0};
		gint _tmp10_ = 0;
#line 56 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
		_tmp3_ = self->main_view;
#line 56 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
		_tmp4_ = gd_main_view_get_generic_view (_tmp3_);
#line 56 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
		_tmp5_ = path;
#line 56 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
		gtk_icon_view_get_cell_rect (G_TYPE_CHECK_INSTANCE_TYPE (_tmp4_, GTK_TYPE_ICON_VIEW) ? ((GtkIconView*) _tmp4_) : NULL, _tmp5_, NULL, &_tmp6_);
#line 56 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
		rect = _tmp6_;
#line 57 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
		_tmp7_ = rect;
#line 57 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
		_tmp8_ = _tmp7_.x;
#line 57 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
		_vala_x = (gfloat) _tmp8_;
#line 58 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
		_tmp9_ = rect;
#line 58 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
		_tmp10_ = _tmp9_.y;
#line 58 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
		_vala_y = (gfloat) _tmp10_;
#line 724 "collection-view.c"
	} else {
#line 60 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
		_vala_x = 0.0f;
#line 61 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
		_vala_y = 0.0f;
#line 730 "collection-view.c"
	}
#line 52 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
	_gtk_tree_path_free0 (path);
#line 52 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
	if (x) {
#line 52 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
		*x = _vala_x;
#line 738 "collection-view.c"
	}
#line 52 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
	if (y) {
#line 52 "/extra-data/checkout/gnome/gnome-boxes/src/collection-view.vala"
		*y = _vala_y;
#line 744 "collection-view.c"
	}
}
