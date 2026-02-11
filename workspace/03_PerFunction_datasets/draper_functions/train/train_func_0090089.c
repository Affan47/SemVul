gconf_defaults_unset_mandatory (GConfDefaults          *mechanism,
                                const char            **includes,
                                const char            **excludes,
                                DBusGMethodInvocation  *context)
{
	UnsetData *udata;
	ActionData *adata;

	start_operation ();

	udata = g_new0 (UnsetData, 1);
	udata->mechanism = g_object_ref (mechanism);
	udata->context = context;
	udata->includes = g_strdupv ((gchar **)includes);
	udata->excludes = g_strdupv ((gchar **)excludes);

	adata = g_new0 (ActionData, 1);
	adata->mechanism = g_object_ref (mechanism);
	adata->context = context;
	adata->includes = g_strdupv ((gchar **)includes);
	adata->auth_obtained_callback = do_unset_authorized;
	adata->data = udata;
	adata->destroy = unset_data_free;

	adata->annotation_key = "org.gnome.gconf.defaults.set-mandatory.prefix";
	adata->default_action = "org.gnome.gconf.defaults.set-mandatory";

	polkit_authority_enumerate_actions (mechanism->priv->auth,
					    NULL,
					    actions_ready_cb,
					    adata);
}
