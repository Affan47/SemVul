boxes_vm_configurator_set_sound_config (GVirConfigDomain* domain, BoxesInstallerMedia* install_media) {
	GVirConfigDomainSound* sound = NULL;
	GVirConfigDomainSound* _tmp0_ = NULL;
	OsinfoDevice* device = NULL;
	BoxesInstallerMedia* _tmp1_ = NULL;
	OsinfoDeviceList* _tmp2_ = NULL;
	OsinfoDeviceList* _tmp3_ = NULL;
	OsinfoDeviceList* _tmp4_ = NULL;
	OsinfoDevice* _tmp5_ = NULL;
	OsinfoDevice* _tmp6_ = NULL;
	gint _tmp7_ = 0;
	OsinfoDevice* _tmp8_ = NULL;
	gint model = 0;
	gint _tmp12_ = 0;
	GVirConfigDomainSound* _tmp13_ = NULL;
	GVirConfigDomain* _tmp14_ = NULL;
	GVirConfigDomainSound* _tmp15_ = NULL;
#line 257 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	g_return_if_fail (domain != NULL);
#line 257 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	g_return_if_fail (install_media != NULL);
#line 258 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp0_ = gvir_config_domain_sound_new ();
#line 258 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	sound = _tmp0_;
#line 259 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp1_ = install_media;
#line 259 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp2_ = boxes_installer_media_get_supported_devices (_tmp1_);
#line 259 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp3_ = _tmp2_;
#line 259 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp4_ = _tmp3_;
#line 259 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp5_ = boxes_find_device_by_prop (_tmp4_, OSINFO_DEVICE_PROP_CLASS, "audio");
#line 259 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp6_ = _tmp5_;
#line 259 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_g_object_unref0 (_tmp4_);
#line 259 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	device = _tmp6_;
#line 260 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp8_ = device;
#line 260 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	if (_tmp8_ != NULL) {
#line 1495 "vm-configurator.c"
		OsinfoDevice* _tmp9_ = NULL;
		const gchar* _tmp10_ = NULL;
		gint _tmp11_ = 0;
#line 260 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
		_tmp9_ = device;
#line 260 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
		_tmp10_ = osinfo_device_get_name (_tmp9_);
#line 260 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
		_tmp11_ = boxes_get_enum_value (_tmp10_, gvir_config_domain_sound_model_get_type ());
#line 260 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
		_tmp7_ = _tmp11_;
#line 1507 "vm-configurator.c"
	} else {
#line 261 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
		_tmp7_ = (gint) GVIR_CONFIG_DOMAIN_SOUND_MODEL_AC97;
#line 1511 "vm-configurator.c"
	}
#line 260 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp12_ = _tmp7_;
#line 260 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	model = _tmp12_;
#line 262 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	g_return_if_fail (model != (-1));
#line 263 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp13_ = sound;
#line 263 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	gvir_config_domain_sound_set_model (_tmp13_, (GVirConfigDomainSoundModel) model);
#line 265 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp14_ = domain;
#line 265 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp15_ = sound;
#line 265 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	gvir_config_domain_add_device (_tmp14_, (GVirConfigDomainDevice*) _tmp15_);
#line 257 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_g_object_unref0 (device);
#line 257 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_g_object_unref0 (sound);
#line 1533 "vm-configurator.c"
}
