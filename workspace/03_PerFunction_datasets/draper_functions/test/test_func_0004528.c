plugin_set_info (PluginInfo* info) {
	PluginInfo* _tmp0_;
	g_return_if_fail (info != NULL);
	_tmp0_ = info;
	geany_vala_plugin_SET_INFO (_tmp0_, "MultiTerm", "Multi-tabbed virtual terminal emulator.", "0.1", "Matthew Brush <matt@geany.org>");
}
