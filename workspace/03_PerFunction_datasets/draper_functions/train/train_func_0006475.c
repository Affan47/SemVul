boxes_vm_configurator_get_num_reboots (GVirConfigDomain* domain) {
	guint result = 0U;
	gchar* str = NULL;
	GVirConfigDomain* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	gint _tmp2_ = 0;
	const gchar* _tmp3_ = NULL;
#line 169 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	g_return_val_if_fail (domain != NULL, 0U);
#line 170 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp0_ = domain;
#line 170 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp1_ = boxes_vm_configurator_get_custom_xml_node (_tmp0_, "num-reboots");
#line 170 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	str = _tmp1_;
#line 171 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp3_ = str;
#line 171 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	if (_tmp3_ != NULL) {
#line 993 "vm-configurator.c"
		const gchar* _tmp4_ = NULL;
		gint _tmp5_ = 0;
#line 171 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
		_tmp4_ = str;
#line 171 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
		_tmp5_ = atoi (_tmp4_);
#line 171 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
		_tmp2_ = _tmp5_;
#line 1002 "vm-configurator.c"
	} else {
#line 171 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
		_tmp2_ = 0;
#line 1006 "vm-configurator.c"
	}
#line 171 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	result = (guint) _tmp2_;
#line 171 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_g_free0 (str);
#line 171 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	return result;
#line 1014 "vm-configurator.c"
}
