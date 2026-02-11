clutter_context_get_default_unlocked (void)
{
  if (G_UNLIKELY (ClutterCntx == NULL))
    {
      ClutterMainContext *ctx;

      ClutterCntx = ctx = g_new0 (ClutterMainContext, 1);

      ctx->is_initialized = FALSE;


      ctx->backend = _clutter_create_backend ();


      ctx->settings = clutter_settings_get_default ();
      _clutter_settings_set_backend (ctx->settings, ctx->backend);

      ctx->motion_events_per_actor = TRUE;
      ctx->last_repaint_id = 1;
    }

  return ClutterCntx;
}
