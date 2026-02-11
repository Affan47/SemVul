hb_gobject_buffer_content_type_get_type (void)
{
  static gsize type_id = 0;

  if (g_once_init_enter (&type_id))
    {
      static const GEnumValue values[] = {
        { HB_BUFFER_CONTENT_TYPE_INVALID, "HB_BUFFER_CONTENT_TYPE_INVALID", "invalid" },
        { HB_BUFFER_CONTENT_TYPE_UNICODE, "HB_BUFFER_CONTENT_TYPE_UNICODE", "unicode" },
        { HB_BUFFER_CONTENT_TYPE_GLYPHS, "HB_BUFFER_CONTENT_TYPE_GLYPHS", "glyphs" },
        { 0, NULL, NULL }
      };
      GType id =
        g_enum_register_static (g_intern_static_string ("hb_buffer_content_type_t"), values);
      g_once_init_leave (&type_id, id);
    }

  return type_id;
}
