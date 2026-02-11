tracker_preferences_spinbutton_delay_value_changed_cb (GtkSpinButton* source, TrackerPreferences* self) {
	GSettings* _tmp0_ = NULL;
	GtkSpinButton* _tmp1_ = NULL;
	gint _tmp2_ = 0;
#line 295 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-preferences/tracker-preferences.vala"
	g_return_if_fail (self != NULL);
#line 295 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-preferences/tracker-preferences.vala"
	g_return_if_fail (source != NULL);
#line 296 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-preferences/tracker-preferences.vala"
	_tmp0_ = self->priv->settings_miner_fs;
#line 296 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-preferences/tracker-preferences.vala"
	_tmp1_ = source;
#line 296 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-preferences/tracker-preferences.vala"
	_tmp2_ = gtk_spin_button_get_value_as_int (_tmp1_);
#line 296 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-preferences/tracker-preferences.vala"
	g_settings_set_int (_tmp0_, "initial-sleep", _tmp2_);
#line 1523 "tracker-preferences.c"
}
