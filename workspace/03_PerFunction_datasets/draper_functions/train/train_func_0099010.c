FreeImage_Open(PluginNode *node, FreeImageIO *io, fi_handle handle, BOOL open_for_reading) {
	if (node->m_plugin->open_proc != NULL) {
       return node->m_plugin->open_proc(io, handle, open_for_reading);
	}

	return NULL;
}
