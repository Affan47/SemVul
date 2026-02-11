gth_browser_get_file_modified (GthBrowser *browser)
{
	if (browser->priv->current_file != NULL)
		return g_file_info_get_attribute_boolean (browser->priv->current_file->info, "gth::file::is-modified");
	else
		return FALSE;
}
