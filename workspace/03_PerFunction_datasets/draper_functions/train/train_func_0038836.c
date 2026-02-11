boxes_vm_configurator_set_os_config (GVirConfigDomain* domain, BoxesInstallerMedia* install_media, GVirConfigCapabilitiesGuest* guest_caps) {
	GVirConfigDomainOs* os = NULL;
	GVirConfigDomainOs* _tmp0_ = NULL;
	GVirConfigCapabilitiesGuest* _tmp1_ = NULL;
	GVirConfigCapabilitiesGuestArch* _tmp2_ = NULL;
	GVirConfigCapabilitiesGuestArch* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	GList* boot_devices = NULL;
	BoxesInstallerMedia* _tmp5_ = NULL;
	GVirConfigDomain* _tmp6_ = NULL;
#line 232 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	g_return_if_fail (domain != NULL);
#line 232 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	g_return_if_fail (install_media != NULL);
#line 232 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	g_return_if_fail (guest_caps != NULL);
#line 233 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp0_ = gvir_config_domain_os_new ();
#line 233 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	os = _tmp0_;
#line 234 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	gvir_config_domain_os_set_os_type (os, GVIR_CONFIG_DOMAIN_OS_TYPE_HVM);
#line 235 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp1_ = guest_caps;
#line 235 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp2_ = gvir_config_capabilities_guest_get_arch (_tmp1_);
#line 235 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp3_ = _tmp2_;
#line 235 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp4_ = gvir_config_capabilities_guest_arch_get_name (_tmp3_);
#line 235 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	gvir_config_domain_os_set_arch (os, _tmp4_);
#line 235 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_g_object_unref0 (_tmp3_);
#line 237 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	boot_devices = NULL;
#line 238 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp5_ = install_media;
#line 238 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	boxes_installer_media_set_direct_boot_params (_tmp5_, os);
#line 239 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	boot_devices = g_list_append (boot_devices, (gpointer) ((gintptr) GVIR_CONFIG_DOMAIN_OS_BOOT_DEVICE_CDROM));
#line 240 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	boot_devices = g_list_append (boot_devices, (gpointer) ((gintptr) GVIR_CONFIG_DOMAIN_OS_BOOT_DEVICE_HD));
#line 241 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	gvir_config_domain_os_set_boot_devices (os, boot_devices);
#line 243 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp6_ = domain;
#line 243 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	gvir_config_domain_set_os (_tmp6_, os);
#line 232 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_g_list_free0 (boot_devices);
#line 232 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_g_object_unref0 (os);
#line 1359 "vm-configurator.c"
}
