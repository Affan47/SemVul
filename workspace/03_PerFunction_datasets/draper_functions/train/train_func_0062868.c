cgu_present_cb(GDBusConnection*,
			   const gchar*,
			   const gchar*,
			   const gchar*,
			   const gchar* method_name,
			   GVariant* parameters,
			   GDBusMethodInvocation* invocation,
			   void*) {

  if (!g_strcmp0(method_name, "Present")) {

    gboolean ret;

    if (!cgu_present_items.func)
      ret = FALSE;
    else {


      GvarHandle decomposed(g_variant_get_child_value(parameters, 0));


      decomposed.reset(g_variant_get_variant(decomposed));


      if (!g_variant_type_equal(g_variant_get_type(decomposed), G_VARIANT_TYPE_BOOLEAN)) {
	const gchar** ar = g_variant_get_bytestring_array(decomposed, 0);
	ret = cgu_present_items.func(cgu_present_items.data, (const char**)ar);
	g_free(ar);
      }
      else
	ret = cgu_present_items.func(cgu_present_items.data, 0);
    }

    if (!ret) {
      g_dbus_method_invocation_return_error(invocation,
					    cgu_prog_presenter_error_get_quark(),
					    CGU_PROG_PRESENTER_FALSE,
					    "%s",
					    "Cgu::PresentFunc function returned FALSE");
    }
    else
      g_dbus_method_invocation_return_value(invocation, 0);
  }
  else
    g_warning("ProgPresenter call to invalid method name\n");
}
