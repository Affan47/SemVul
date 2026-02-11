up_wakeups_get_data_sync (UpWakeups *wakeups, GCancellable *cancellable, GError **error)
{
	GError *error_local = NULL;
	GType g_type_gvalue_array;
	GPtrArray *gvalue_ptr_array = NULL;
	GValueArray *gva;
	GValue *gv;
	guint i;
	UpWakeupItem *item;
	GPtrArray *array = NULL;
	gboolean ret;

	g_return_val_if_fail (UP_IS_WAKEUPS (wakeups), NULL);
	g_return_val_if_fail (wakeups->priv->proxy != NULL, NULL);

	g_type_gvalue_array = dbus_g_type_get_collection ("GPtrArray",
					dbus_g_type_get_struct("GValueArray",
						G_TYPE_BOOLEAN,
						G_TYPE_UINT,
						G_TYPE_DOUBLE,
						G_TYPE_STRING,
						G_TYPE_STRING,
						G_TYPE_INVALID));


	ret = dbus_g_proxy_call (wakeups->priv->proxy, "GetData", &error_local,
				 G_TYPE_INVALID,
				 g_type_gvalue_array, &gvalue_ptr_array,
				 G_TYPE_INVALID);
	if (!ret) {
		g_warning ("GetData on failed: %s", error_local->message);
		g_set_error (error, 1, 0, "%s", error_local->message);
		g_error_free (error_local);
		goto out;
	}


	if (gvalue_ptr_array->len == 0)
		goto out;


	array = g_ptr_array_new_with_free_func ((GDestroyNotify) g_object_unref);
	for (i=0; i<gvalue_ptr_array->len; i++) {
		gva = (GValueArray *) g_ptr_array_index (gvalue_ptr_array, i);
		item = up_wakeup_item_new ();


		gv = g_value_array_get_nth (gva, 0);
		up_wakeup_item_set_is_userspace (item, g_value_get_boolean (gv));
		g_value_unset (gv);


		gv = g_value_array_get_nth (gva, 1);
		up_wakeup_item_set_id (item, g_value_get_uint (gv));
		g_value_unset (gv);


		gv = g_value_array_get_nth (gva, 2);
		up_wakeup_item_set_value (item, g_value_get_double (gv));
		g_value_unset (gv);


		gv = g_value_array_get_nth (gva, 3);
		up_wakeup_item_set_cmdline (item, g_value_get_string (gv));
		g_value_unset (gv);


		gv = g_value_array_get_nth (gva, 4);
		up_wakeup_item_set_details (item, g_value_get_string (gv));
		g_value_unset (gv);


		g_ptr_array_add (array, item);
		g_value_array_free (gva);
	}
out:
	if (gvalue_ptr_array != NULL)
		g_ptr_array_unref (gvalue_ptr_array);
	return array;
}
