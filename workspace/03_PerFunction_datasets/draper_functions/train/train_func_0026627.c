clutter_stage_ensure_current (ClutterStage *stage)
{
  ClutterBackend *backend;

  g_return_if_fail (CLUTTER_IS_STAGE (stage));

  backend = clutter_get_default_backend ();
  _clutter_backend_ensure_context (backend, stage);
}
