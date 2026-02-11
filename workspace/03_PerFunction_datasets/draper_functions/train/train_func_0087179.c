write_return_value_attributes (Xml *file,
                               GICallableInfo *info)
{
  GIAttributeIter iter = { 0, };
  char *name, *value;

  while (g_callable_info_iterate_return_attributes (info, &iter, &name, &value))
    {
      xml_start_element (file, "attribute");
      xml_printf (file, " name=\"%s\" value=\"%s\"", name, value);
      xml_end_element (file, "attribute");
    }
}
