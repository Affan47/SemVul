__lambda73_ (BoxesProperties* self) {
	BoxesLibvirtMachine* machine = NULL;
	BoxesApp* _tmp0_ = NULL;
	BoxesCollectionItem* _tmp1_ = NULL;
	BoxesLibvirtMachine* _tmp2_ = NULL;
	BoxesLibvirtMachine* _tmp3_ = NULL;
#line 295 "/extra-data/checkout/gnome/gnome-boxes/src/properties.vala"
	_tmp0_ = boxes_app_app;
#line 295 "/extra-data/checkout/gnome/gnome-boxes/src/properties.vala"
	_tmp1_ = _tmp0_->current_item;
#line 295 "/extra-data/checkout/gnome/gnome-boxes/src/properties.vala"
	_tmp2_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp1_, BOXES_TYPE_LIBVIRT_MACHINE) ? ((BoxesLibvirtMachine*) _tmp1_) : NULL);
#line 295 "/extra-data/checkout/gnome/gnome-boxes/src/properties.vala"
	machine = _tmp2_;
#line 296 "/extra-data/checkout/gnome/gnome-boxes/src/properties.vala"
	_tmp3_ = machine;
#line 296 "/extra-data/checkout/gnome/gnome-boxes/src/properties.vala"
	if (_tmp3_ != NULL) {
#line 1141 "properties.c"
		BoxesLibvirtMachine* _tmp4_ = NULL;
#line 297 "/extra-data/checkout/gnome/gnome-boxes/src/properties.vala"
		_tmp4_ = machine;
#line 297 "/extra-data/checkout/gnome/gnome-boxes/src/properties.vala"
		boxes_libvirt_machine_force_shutdown (_tmp4_, TRUE);
#line 1147 "properties.c"
	}
#line 294 "/extra-data/checkout/gnome/gnome-boxes/src/properties.vala"
	_g_object_unref0 (machine);
#line 1151 "properties.c"
}
