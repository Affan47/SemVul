model_recomposite_icon (GeditFileBrowserStore *tree_model,
			GtkTreeIter           *iter)
{
	g_return_if_fail (GEDIT_IS_FILE_BROWSER_STORE (tree_model));
	g_return_if_fail (iter != NULL);
	g_return_if_fail (iter->user_data != NULL);

	model_recomposite_icon_real (tree_model,
				     (FileBrowserNode *) (iter->user_data),
				     NULL);
}
