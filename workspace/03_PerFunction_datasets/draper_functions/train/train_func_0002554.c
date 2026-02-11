_boxes_machine_display___lambda160_ (BoxesMachine* self, gint id) {
	BoxesApp* _tmp0_ = NULL;
	BoxesDisplayPage* _tmp1_ = NULL;
	GtkWidget* _tmp2_ = NULL;
	GtkWidget* _tmp3_ = NULL;
#line 139 "/extra-data/checkout/gnome/gnome-boxes/src/machine.vala"
	_tmp0_ = boxes_app_app;
#line 139 "/extra-data/checkout/gnome/gnome-boxes/src/machine.vala"
	_tmp1_ = _tmp0_->display_page;
#line 139 "/extra-data/checkout/gnome/gnome-boxes/src/machine.vala"
	_tmp2_ = boxes_display_page_remove_display (_tmp1_);
#line 139 "/extra-data/checkout/gnome/gnome-boxes/src/machine.vala"
	_tmp3_ = _tmp2_;
#line 139 "/extra-data/checkout/gnome/gnome-boxes/src/machine.vala"
	_g_object_unref0 (_tmp3_);
#line 4184 "machine.c"
}
