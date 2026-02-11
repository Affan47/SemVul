FreeImage_LoadFromHandle(FREE_IMAGE_FORMAT fif, FreeImageIO *io, fi_handle handle, int flags) {
	if ((fif >= 0) && (fif < FreeImage_GetFIFCount())) {
		PluginNode *node = s_plugins->FindNodeFromFIF(fif);

		if (node != NULL) {
			if(node->m_plugin->load_proc != NULL) {
				void *data = FreeImage_Open(node, io, handle, TRUE);

				FIBITMAP *bitmap = node->m_plugin->load_proc(io, handle, -1, flags, data);

				FreeImage_Close(node, io, handle, data);

				return bitmap;
			}
		}
	}

	return NULL;
}
