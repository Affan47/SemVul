gedit_file_browser_store_get_root (GeditFileBrowserStore *model)
{
	g_return_val_if_fail (GEDIT_IS_FILE_BROWSER_STORE (model), NULL);

	if (model->priv->root == NULL || model->priv->root->file == NULL)
		return NULL;
	else
		return g_file_dup (model->priv->root->file);
}
