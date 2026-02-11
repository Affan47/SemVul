___lambda2_ (GmpcEasyCommand* self, GtkEntry* source, GtkEntryIconPosition pos, GdkEvent* event) {
	GtkEntryIconPosition _tmp0_;
	g_return_if_fail (source != NULL);
	g_return_if_fail (event != NULL);
	_tmp0_ = pos;
	if (_tmp0_ == GTK_ENTRY_ICON_SECONDARY) {
		GtkEntry* _tmp1_;
		_tmp1_ = source;
		gtk_entry_set_text (_tmp1_, "");
	} else {
		gmpc_easy_command_popup_destroy (self);
	}
}
