file_browser_refresh (FileBrowser* self) {
	GFile* _tmp0_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->_current_directory;
	file_browser_set_directory (self, _tmp0_, TRUE);
}
