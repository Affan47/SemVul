write_field_info (const gchar *namespace,
		  GIFieldInfo *info,
		  GIConstantInfo *branch,
		  Xml         *file)
{
  const gchar *name;
  GIFieldInfoFlags flags;
  gint size;
  gint offset;
  GITypeInfo *type;
  GIBaseInfo *interface;
  GIArgument value;

  name = g_base_info_get_name ((GIBaseInfo *)info);
  flags = g_field_info_get_flags (info);
  size = g_field_info_get_size (info);
  offset = g_field_info_get_offset (info);

  xml_start_element (file, "field");
  xml_printf (file, " name=\"%s\"", name);


  if (!(flags & GI_FIELD_IS_READABLE))
    xml_printf (file, " readable=\"0\"");
  if (flags & GI_FIELD_IS_WRITABLE)
    xml_printf (file, " writable=\"1\"");

  if (size)
    xml_printf (file, " bits=\"%d\"", size);

  write_attributes (file, (GIBaseInfo*) info);

  type = g_field_info_get_type (info);

  if (branch)
    {
      xml_printf (file, " branch=\"");
      type = g_constant_info_get_type (branch);
      g_constant_info_get_value (branch, &value);
      write_constant_value (namespace, type, &value, file);
      xml_printf (file, "\"");
    }

  if (file->show_all)
    {
      if (offset >= 0)
        xml_printf (file, "offset=\"%d\"", offset);
    }

  interface = g_type_info_get_interface (type);
  if (interface && g_base_info_get_type(interface) == GI_INFO_TYPE_CALLBACK)
    write_callback_info (namespace, (GICallbackInfo *)interface, file);
  else
    write_type_info (namespace, type, file);

  if (interface)
    g_base_info_unref (interface);

  g_base_info_unref ((GIBaseInfo *)type);

  xml_end_element (file, "field");
}
