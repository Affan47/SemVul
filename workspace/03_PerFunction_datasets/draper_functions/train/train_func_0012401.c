open_policy_on_export_click(GtkButton * button __attribute__ ((unused)), gpointer user_data)
{
	struct open_policy *op = (struct open_policy *)user_data;
	char *path = util_save_file(GTK_WINDOW(op->dialog), "Export Policy List", NULL);
	apol_policy_path_t *ppath = NULL;
	if (path == NULL) {
		return;
	}
	ppath = open_policy_build_path(op);
	if (ppath == NULL) {
		goto cleanup;
	}
	if (apol_policy_path_to_file(ppath, path) < 0) {
		toplevel_ERR(op->top, "Error exporting policy list %s: %s", path, strerror(errno));
	}
      cleanup:
	g_free(path);
	apol_policy_path_destroy(&ppath);
}
