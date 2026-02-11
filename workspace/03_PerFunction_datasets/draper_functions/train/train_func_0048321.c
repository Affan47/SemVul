set_cursor_visible (ClutterStageX11 *stage_x11)
{
  ClutterStageCogl *stage_cogl = CLUTTER_STAGE_COGL (stage_x11);
  ClutterBackendX11 *backend_x11 = CLUTTER_BACKEND_X11 (stage_cogl->backend);

  if (stage_x11->xwin == None)
    return;

  CLUTTER_NOTE (BACKEND, "setting cursor state ('%s') over stage window (%u)",
                stage_x11->is_cursor_visible ? "visible" : "invisible",
                (unsigned int) stage_x11->xwin);

  if (stage_x11->is_cursor_visible)
    {
      XUndefineCursor (backend_x11->xdpy, stage_x11->xwin);
    }
  else
    {
      XColor col;
      Pixmap pix;
      Cursor curs;

      pix = XCreatePixmap (backend_x11->xdpy, stage_x11->xwin, 1, 1, 1);
      memset (&col, 0, sizeof (col));
      curs = XCreatePixmapCursor (backend_x11->xdpy,
                                  pix, pix,
                                  &col, &col,
                                  1, 1);
      XFreePixmap (backend_x11->xdpy, pix);
      XDefineCursor (backend_x11->xdpy, stage_x11->xwin, curs);
    }
}
