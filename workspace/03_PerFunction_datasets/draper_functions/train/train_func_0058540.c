settings_update_fontmap (ClutterSettings *self,
                         guint            stamp)
{
  if (self->backend == NULL)
    return;

#ifdef HAVE_PANGO_FT2
  CLUTTER_NOTE (BACKEND, "Update fontmaps (stamp: %d)", stamp);

  if (self->last_fontconfig_timestamp != stamp)
    {
      ClutterMainContext *context;
      gboolean update_needed = FALSE;

      context = _clutter_context_get_default ();


      if (context->font_map)
        {
          PangoFontMap *fontmap = PANGO_FONT_MAP (context->font_map);

          if (PANGO_IS_FC_FONT_MAP (fontmap) &&
              !FcConfigUptoDate (NULL))
            {
              pango_fc_font_map_cache_clear (PANGO_FC_FONT_MAP (fontmap));

              if (FcInitReinitialize ())
                update_needed = TRUE;
            }
        }

      self->last_fontconfig_timestamp = stamp;

      if (update_needed)
        g_signal_emit_by_name (self->backend, "font-changed");
    }
#endif
}
