tracker_preferences_checkbutton_enable_index_on_battery_toggled_cb (GtkCheckButton* source, TrackerPreferences* self) {
	GSettings* _tmp0_;
	GtkCheckButton* _tmp1_;
	gboolean _tmp2_;
	gboolean _tmp3_;
	GtkCheckButton* _tmp4_;
	GtkCheckButton* _tmp5_;
	gboolean _tmp6_;
	gboolean _tmp7_;
#line 305 "/home/martyn/Source/tracker/src/tracker-preferences/tracker-preferences.vala"
	g_return_if_fail (self != NULL);
#line 305 "/home/martyn/Source/tracker/src/tracker-preferences/tracker-preferences.vala"
	g_return_if_fail (source != NULL);
#line 306 "/home/martyn/Source/tracker/src/tracker-preferences/tracker-preferences.vala"
	_tmp0_ = self->priv->settings_miner_fs;
#line 306 "/home/martyn/Source/tracker/src/tracker-preferences/tracker-preferences.vala"
	_tmp1_ = source;
#line 306 "/home/martyn/Source/tracker/src/tracker-preferences/tracker-preferences.vala"
	_tmp2_ = gtk_toggle_button_get_active ((GtkToggleButton*) _tmp1_);
#line 306 "/home/martyn/Source/tracker/src/tracker-preferences/tracker-preferences.vala"
	_tmp3_ = _tmp2_;
#line 306 "/home/martyn/Source/tracker/src/tracker-preferences/tracker-preferences.vala"
	g_settings_set_boolean (_tmp0_, "index-on-battery", _tmp3_);
#line 307 "/home/martyn/Source/tracker/src/tracker-preferences/tracker-preferences.vala"
	_tmp4_ = self->priv->checkbutton_enable_index_on_battery_first_time;
#line 307 "/home/martyn/Source/tracker/src/tracker-preferences/tracker-preferences.vala"
	_tmp5_ = source;
#line 307 "/home/martyn/Source/tracker/src/tracker-preferences/tracker-preferences.vala"
	_tmp6_ = gtk_toggle_button_get_active ((GtkToggleButton*) _tmp5_);
#line 307 "/home/martyn/Source/tracker/src/tracker-preferences/tracker-preferences.vala"
	_tmp7_ = _tmp6_;
#line 307 "/home/martyn/Source/tracker/src/tracker-preferences/tracker-preferences.vala"
	gtk_widget_set_sensitive ((GtkWidget*) _tmp4_, !_tmp7_);
#line 1583 "tracker-preferences.c"
}
