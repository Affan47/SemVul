boxes_vm_configurator_set_num_reboots (GVirConfigDomain* domain, BoxesInstallerMedia* install_media, guint num_reboots) {
	GVirConfigDomain* _tmp0_ = NULL;
	BoxesInstallerMedia* _tmp1_ = NULL;
	guint _tmp2_ = 0U;
#line 174 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	g_return_if_fail (domain != NULL);
#line 174 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	g_return_if_fail (install_media != NULL);
#line 175 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp0_ = domain;
#line 175 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp1_ = install_media;
#line 175 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	_tmp2_ = num_reboots;
#line 175 "/extra-data/checkout/gnome/gnome-boxes/src/vm-configurator.vala"
	boxes_vm_configurator_update_custom_xml (_tmp0_, _tmp1_, _tmp2_, FALSE);
#line 1034 "vm-configurator.c"
}
