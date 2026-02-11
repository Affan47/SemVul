set_foreign_window_callback (ClutterActor *actor,
                             void         *data)
{
  ForeignWindowData *fwd = data;
  ClutterStageCogl *stage_cogl = CLUTTER_STAGE_COGL (fwd->stage_x11);
  ClutterBackendX11 *backend_x11 = CLUTTER_BACKEND_X11 (stage_cogl->backend);

  CLUTTER_NOTE (BACKEND, "Setting foreign window (0x%x)",
                (unsigned int) fwd->xwindow);

  if (fwd->destroy_old_xwindow && fwd->stage_x11->xwin != None)
    {
      CLUTTER_NOTE (BACKEND, "Destroying previous window (0x%x)",
                    (unsigned int) fwd->xwindow);
      XDestroyWindow (backend_x11->xdpy, fwd->stage_x11->xwin);
    }

  fwd->stage_x11->xwin = fwd->xwindow;
  fwd->stage_x11->is_foreign_xwin = TRUE;

  fwd->stage_x11->xwin_width = fwd->geom.width * fwd->stage_x11->scale_factor;
  fwd->stage_x11->xwin_height = fwd->geom.height * fwd->stage_x11->scale_factor;

  clutter_actor_set_size (actor, fwd->geom.width, fwd->geom.height);

  if (clutter_stages_by_xid == NULL)
    clutter_stages_by_xid = g_hash_table_new (NULL, NULL);

  g_hash_table_insert (clutter_stages_by_xid,
                       GINT_TO_POINTER (fwd->stage_x11->xwin),
                       fwd->stage_x11);


  clutter_stage_ensure_current (CLUTTER_STAGE (actor));
}
