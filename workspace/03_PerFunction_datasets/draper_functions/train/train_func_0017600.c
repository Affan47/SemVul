test_item_created (Test *test,
                   gconstpointer unused)
{
	const gchar *item;
	const gchar *prompt;
	GError *error = NULL;
	GVariant *properties;
	GVariant *retval;
	GVariant *label;


	label = g_variant_new_dict_entry (g_variant_new_string ("org.freedesktop.Secret.Item.Label"),
	                                  g_variant_new_variant (g_variant_new_string ("My Item")));
	properties = g_variant_new_array (G_VARIANT_TYPE ("{sv}"), &label, 1);

	retval = dbus_call_perform (test,
	                            "/org/freedesktop/secrets/collection/test",
	                            SECRET_COLLECTION_INTERFACE,
	                            "CreateItem",
	                            g_variant_new ("(@a{sv}@(oayays)b)",
	                                           properties,
	                                           test_service_build_secret (&test->service, "booo"),
	                                           FALSE),
	                            G_VARIANT_TYPE ("(oo)"),
	                            &error);
	g_assert_no_error (error);


	g_variant_get (retval, "(&o&o)", &item, &prompt);
	g_assert_cmpstr (item, !=, "/");
	g_assert_cmpstr (prompt, ==, "/");

	expect_signal_with_path (test, "/org/freedesktop/secrets/collection/test",
	                         SECRET_COLLECTION_INTERFACE, "ItemCreated", item);
	expect_property_changed (test, "/org/freedesktop/secrets/collection/test",
	                         SECRET_COLLECTION_INTERFACE, "Items");

	g_variant_unref (retval);
}
