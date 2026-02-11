boxes_unattended_installer_get_user_unattended (BoxesUnattendedInstaller* self, const gchar* suffix) {
	gchar* result = NULL;
	gchar* filename = NULL;
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	const gchar* _tmp8_ = NULL;
	gchar* _tmp9_ = NULL;
#line 355 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
	g_return_val_if_fail (self != NULL, NULL);
#line 356 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
	_tmp0_ = self->priv->hostname;
#line 356 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
	_tmp1_ = g_strdup (_tmp0_);
#line 356 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
	filename = _tmp1_;
#line 357 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
	_tmp2_ = suffix;
#line 357 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
	if (_tmp2_ != NULL) {
#line 3003 "unattended-installer.c"
		const gchar* _tmp3_ = NULL;
		const gchar* _tmp4_ = NULL;
		gchar* _tmp5_ = NULL;
		gchar* _tmp6_ = NULL;
		gchar* _tmp7_ = NULL;
#line 358 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
		_tmp3_ = filename;
#line 358 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
		_tmp4_ = suffix;
#line 358 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
		_tmp5_ = g_strconcat ("-", _tmp4_, NULL);
#line 358 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
		_tmp6_ = _tmp5_;
#line 358 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
		_tmp7_ = g_strconcat (_tmp3_, _tmp6_, NULL);
#line 358 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
		_g_free0 (filename);
#line 358 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
		filename = _tmp7_;
#line 358 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
		_g_free0 (_tmp6_);
#line 3025 "unattended-installer.c"
	}
#line 360 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
	_tmp8_ = filename;
#line 360 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
	_tmp9_ = boxes_get_user_pkgcache (_tmp8_);
#line 360 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
	result = _tmp9_;
#line 360 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
	_g_free0 (filename);
#line 360 "/extra-data/checkout/gnome/gnome-boxes/src/unattended-installer.vala"
	return result;
#line 3037 "unattended-installer.c"
}
