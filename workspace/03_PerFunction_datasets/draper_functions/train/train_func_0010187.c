update_display (p_state *state, Bool changed_only)
{
  int x, y;

  for (y = 0; y < state->grid_height; y++)
    for (x = 0; x < state->grid_width; x++)
      {
        p_cell *cell = &state->cells[state->grid_width * y + x];
        int width, height, tx, ty;

        if (changed_only && !cell->changed)
          continue;

        width = state->char_width * state->scale;
        height = state->char_height * state->scale;
        tx = x * width;
        ty = y * height;

        if (cell->state == BLANK || cell->p_char->blank_p)
          {
            XFillRectangle (state->dpy, state->window, state->gcs[BLANK],
                            tx, ty, width, height);
          }
        else
          {
#ifdef FUZZY_BORDER
            GC gc1 = state->gcs[cell->state];
            GC gc2 = ((cell->state + 2) < state->ticks
                      ? state->gcs[cell->state + 2]
                      : 0);
            GC gc3 = (gc2 ? gc2 : gc1);
            if (gc3)
              XCopyPlane (state->dpy, cell->p_char->pixmap, state->window, gc3,
                          0, 0, width, height, tx, ty, 1L);
            if (gc2)
              {
                XSetClipMask (state->dpy, gc1, cell->p_char->pixmap2);
                XSetClipOrigin (state->dpy, gc1, tx, ty);
                XFillRectangle (state->dpy, state->window, gc1,
                                tx, ty, width, height);
                XSetClipMask (state->dpy, gc1, None);
              }
#else

            XCopyPlane (state->dpy,
                        cell->p_char->pixmap, state->window,
                        state->gcs[cell->state],
                        0, 0, width, height, tx, ty, 1L);

#endif
          }

        cell->changed = False;
      }
}
