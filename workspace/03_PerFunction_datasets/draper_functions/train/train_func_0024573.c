gst_color_effects_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstColorEffects *filter = GST_COLOR_EFFECTS (object);

  switch (prop_id) {
    case PROP_PRESET:
      GST_OBJECT_LOCK (filter);
      filter->preset = g_value_get_enum (value);

      switch (filter->preset) {
        case GST_COLOR_EFFECTS_PRESET_NONE:
          filter->table = NULL;
          break;
        case GST_COLOR_EFFECTS_PRESET_HEAT:
          filter->table = heat_table;
          filter->map_luma = TRUE;
          break;
        case GST_COLOR_EFFECTS_PRESET_SEPIA:
          filter->table = sepia_table;
          filter->map_luma = TRUE;
          break;
        case GST_COLOR_EFFECTS_PRESET_XRAY:
          filter->table = xray_table;
          filter->map_luma = TRUE;
          break;
        case GST_COLOR_EFFECTS_PRESET_XPRO:
          filter->table = xpro_table;
          filter->map_luma = FALSE;
          break;
        case GST_COLOR_EFFECTS_PRESET_YELLOWBLUE:
          filter->table = yellowblue_table;
          filter->map_luma = FALSE;
          break;
        default:
          g_assert_not_reached ();

      }
      GST_OBJECT_UNLOCK (filter);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
