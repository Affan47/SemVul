gegl_buffer_set_property (GObject      *gobject,
                          guint         property_id,
                          const GValue *value,
                          GParamSpec   *pspec)
{
  GeglBuffer *buffer = GEGL_BUFFER (gobject);

  switch (property_id)
    {
      case PROP_X:
        buffer->extent.x = g_value_get_int (value);
        break;

      case PROP_Y:
        buffer->extent.y = g_value_get_int (value);
        break;

      case PROP_WIDTH:
        buffer->extent.width = g_value_get_int (value);
        break;

      case PROP_HEIGHT:
        buffer->extent.height = g_value_get_int (value);
        break;

      case PROP_TILE_HEIGHT:
        buffer->tile_height = g_value_get_int (value);
        break;

      case PROP_TILE_WIDTH:
        buffer->tile_width = g_value_get_int (value);
        break;

      case PROP_PATH:
        if (buffer->path)
          g_free (buffer->path);
        buffer->path = g_value_dup_string (value);
        break;

      case PROP_SHIFT_X:
        buffer->shift_x = g_value_get_int (value);
        break;

      case PROP_SHIFT_Y:
        buffer->shift_y = g_value_get_int (value);
        break;

      case PROP_ABYSS_X:
        buffer->abyss.x = g_value_get_int (value);
        break;

      case PROP_ABYSS_Y:
        buffer->abyss.y = g_value_get_int (value);
        break;

      case PROP_ABYSS_WIDTH:
        buffer->abyss.width = g_value_get_int (value);
        break;

      case PROP_ABYSS_HEIGHT:
        buffer->abyss.height = g_value_get_int (value);
        break;

      case PROP_FORMAT:


        if (g_value_get_pointer (value))
          {
            const Babl *format = g_value_get_pointer (value);


            if (buffer->soft_format)
              {
                gegl_buffer_set_format (buffer, format);
              }
            else
              {
                buffer->format = format;
              }
          }
        break;
      case PROP_BACKEND:
        if (g_value_get_pointer (value))
          buffer->backend = g_value_get_pointer (value);
        break;

      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (gobject, property_id, pspec);
        break;
    }
}
