start_interface (GMarkupParseContext *context,
		 const gchar         *element_name,
		 const gchar        **attribute_names,
		 const gchar        **attribute_values,
		 ParseContext        *ctx,
		 GError             **error)
{
  const gchar *name;
  const gchar *typename;
  const gchar *typeinit;
  const gchar *deprecated;
  const gchar *glib_type_struct;
  GIrNodeInterface *iface;

  if (!(strcmp (element_name, "interface") == 0 &&
	ctx->state == STATE_NAMESPACE))
    return FALSE;

  if (!introspectable_prelude (context, attribute_names, attribute_values, ctx, STATE_INTERFACE))
    return TRUE;

  name = find_attribute ("name", attribute_names, attribute_values);
  typename = find_attribute ("glib:type-name", attribute_names, attribute_values);
  typeinit = find_attribute ("glib:get-type", attribute_names, attribute_values);
  glib_type_struct = find_attribute ("glib:type-struct", attribute_names, attribute_values);
  deprecated = find_attribute ("deprecated", attribute_names, attribute_values);

  if (name == NULL)
    {
      MISSING_ATTRIBUTE (context, error, element_name, "name");
      return FALSE;
    }
  else if (typename == NULL)
    {
      MISSING_ATTRIBUTE (context, error, element_name, "glib:type-name");
      return FALSE;
    }
  else if (typeinit == NULL)
    {
      MISSING_ATTRIBUTE (context, error, element_name, "glib:get-type");
      return FALSE;
    }

  iface = (GIrNodeInterface *) _g_ir_node_new (G_IR_NODE_INTERFACE,
					      ctx->current_module);
  ((GIrNode *)iface)->name = g_strdup (name);
  iface->gtype_name = g_strdup (typename);
  iface->gtype_init = g_strdup (typeinit);
  iface->glib_type_struct = g_strdup (glib_type_struct);
  if (deprecated)
    iface->deprecated = TRUE;
  else
    iface->deprecated = FALSE;

  push_node (ctx, (GIrNode *) iface);
  ctx->current_module->entries =
    g_list_append (ctx->current_module->entries, iface);

  return TRUE;
}
