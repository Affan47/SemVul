idle_preview_thumbnail(gpointer data)
{
  if (thumbnail_data && adjusted_thumbnail_data && do_update_thumbnail)
    {
      thumbnail_update_pending = TRUE;
      set_orientation(pv->orientation);
      if (thumbnail_needs_rebuild && compute_thumbnail(pv->v))
	{
	  set_thumbnail_orientation();
	  redraw_color_swatch ();
	}
      do_preview_thumbnail();
    }
  thumbnail_update_pending = FALSE;
  return FALSE;
}
