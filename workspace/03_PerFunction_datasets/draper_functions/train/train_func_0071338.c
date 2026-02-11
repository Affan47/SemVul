impl_dispatch (Handler *h,
               const char *str_action,
               GHashTable *connection_hash,
               GHashTable *connection_props,
               GHashTable *device_props,
               GHashTable *device_ip4_props,
               GHashTable *device_ip6_props,
               GHashTable *device_dhcp4_props,
               GHashTable *device_dhcp6_props,
               const char *vpn_ip_iface,
               GHashTable *vpn_ip4_props,
               GHashTable *vpn_ip6_props,
               DBusGMethodInvocation *context)
{
	GSList *sorted_scripts = NULL;
	GSList *iter;
	Request *request;
	char **p;
	char *iface = NULL;

	sorted_scripts = find_scripts ();

	if (!sorted_scripts) {
		dbus_g_method_return (context, g_ptr_array_new ());
		return;
	}

	quit_timeout_reschedule (h);

	request = g_malloc0 (sizeof (*request));
	request->handler = h;
	request->context = context;
	request->action = g_strdup (str_action);

	request->envp = nm_dispatcher_utils_construct_envp (str_action,
	                                                    connection_hash,
	                                                    connection_props,
	                                                    device_props,
	                                                    device_ip4_props,
	                                                    device_ip6_props,
	                                                    device_dhcp4_props,
	                                                    device_dhcp6_props,
	                                                    vpn_ip_iface,
	                                                    vpn_ip4_props,
	                                                    vpn_ip6_props,
	                                                    &iface);

	if (debug) {
		g_message ("------------ Action ID %p '%s' Interface %s Environment ------------",
		           context, str_action, iface ? iface : "(none)");
		for (p = request->envp; *p; p++)
			g_message ("  %s", *p);
		g_message ("\n");
	}

	request->iface = g_strdup (iface);

	request->scripts = g_ptr_array_sized_new (5);
	for (iter = sorted_scripts; iter; iter = g_slist_next (iter)) {
		ScriptInfo *s = g_malloc0 (sizeof (*s));
		s->request = request;
		s->script = iter->data;
		g_ptr_array_add (request->scripts, s);
	}
	g_slist_free (sorted_scripts);


	dispatch_one_script (request);
}
