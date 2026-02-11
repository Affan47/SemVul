gst_message_parse_structure_change (GstMessage * message,
    GstStructureChangeType * type, GstElement ** owner, gboolean * busy)
{
  const GValue *owner_gvalue;
  GstStructure *structure;

  g_return_if_fail (GST_IS_MESSAGE (message));
  g_return_if_fail (GST_MESSAGE_TYPE (message) == GST_MESSAGE_STRUCTURE_CHANGE);

  structure = GST_MESSAGE_STRUCTURE (message);
  owner_gvalue = gst_structure_id_get_value (structure, GST_QUARK (OWNER));
  g_return_if_fail (owner_gvalue != NULL);
  g_return_if_fail (G_VALUE_TYPE (owner_gvalue) == GST_TYPE_ELEMENT);

  if (type)
    *type = (GstStructureChangeType)
        g_value_get_enum (gst_structure_id_get_value (structure,
            GST_QUARK (TYPE)));
  if (owner)
    *owner = (GstElement *) g_value_get_object (owner_gvalue);
  if (busy)
    *busy =
        g_value_get_boolean (gst_structure_id_get_value (structure,
            GST_QUARK (BUSY)));
}
