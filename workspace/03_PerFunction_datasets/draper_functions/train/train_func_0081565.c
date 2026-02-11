users_model_filter (GtkTreeModel *model, GtkTreeIter *iter, gpointer data)
{
	GstUsersTool *tool = (GstUsersTool *) data;
	OobsUser *user;
	gint uid;
	gboolean show;

	gtk_tree_model_get (model, iter,
			    COL_USER_ID, &uid,
	                    COL_USER_OBJECT, &user,
			    -1);

	if (user == NULL)
		return FALSE;

	show = (tool->showall
	        || (oobs_user_is_root (user) && tool->showroot)
	        || (uid >= tool->minimum_uid && uid <= tool->maximum_uid)
	        || oobs_self_config_is_user_self (OOBS_SELF_CONFIG (tool->self_config), user));

	g_object_unref (user);

	return show;
}
