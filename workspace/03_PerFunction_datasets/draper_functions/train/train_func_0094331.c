clutter_x11_set_stage_foreign (ClutterStage *stage,
                               Window        xwindow)
{
  ClutterBackendX11 *backend_x11;
  ClutterStageX11 *stage_x11;
  ClutterStageCogl *stage_cogl;
  ClutterStageWindow *impl;
  ClutterActor *actor;
  gint x, y;
  guint width, height, border, depth;
  Window root_return;
  Status status;
  ForeignWindowData fwd;
  XVisualInfo *xvisinfo;

  g_return_val_if_fail (CLUTTER_IS_STAGE (stage), FALSE);
  g_return_val_if_fail (!CLUTTER_ACTOR_IN_DESTRUCTION (stage), FALSE);
  g_return_val_if_fail (xwindow != None, FALSE);

  impl = _clutter_stage_get_window (stage);
  stage_x11 = CLUTTER_STAGE_X11 (impl);
  stage_cogl = CLUTTER_STAGE_COGL (impl);
  backend_x11 = CLUTTER_BACKEND_X11 (stage_cogl->backend);

  xvisinfo = _clutter_backend_x11_get_visual_info (backend_x11);
  g_return_val_if_fail (xvisinfo != NULL, FALSE);

  clutter_x11_trap_x_errors ();

  status = XGetGeometry (backend_x11->xdpy, xwindow,
                         &root_return,
                         &x, &y,
                         &width, &height,
                         &border,
                         &depth);

  if (clutter_x11_untrap_x_errors () || !status)
    {
      g_critical ("Unable to retrieve the geometry of the foreign window: "
                  "XGetGeometry() failed (status code: %d)", status);
      return FALSE;
    }

  if (width == 0 || height == 0)
    {
      g_warning ("The size of the foreign window is 0x0");
      return FALSE;
    }

  if (depth != xvisinfo->depth)
    {
      g_warning ("The depth of the visual of the foreign window is %d, but "
                 "Clutter has been initialized to require a visual depth "
                 "of %d",
                 depth,
                 xvisinfo->depth);
      return FALSE;
    }

  fwd.stage_x11 = stage_x11;
  fwd.xwindow = xwindow;


  if (stage_x11->xwin != None && !stage_x11->is_foreign_xwin)
    fwd.destroy_old_xwindow = TRUE;
  else
    fwd.destroy_old_xwindow = FALSE;

  fwd.geom.x = x;
  fwd.geom.y = y;
  fwd.geom.width = width / stage_x11->scale_factor;
  fwd.geom.height = height / stage_x11->scale_factor;

  actor = CLUTTER_ACTOR (stage);

  _clutter_actor_rerealize (actor,
                            set_foreign_window_callback,
                            &fwd);


  clutter_actor_queue_relayout (actor);

  return TRUE;
}
