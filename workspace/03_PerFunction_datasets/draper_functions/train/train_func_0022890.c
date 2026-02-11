meta_frames_unflicker_bg (MetaFrames *frames,
                          Window      xwindow,
                          int         target_width,
                          int         target_height)
{
  MetaUIFrame *frame;

  frame = meta_frames_lookup_window (frames, xwindow);
  g_return_if_fail (frame != NULL);

  set_background_none (GDK_DISPLAY_XDISPLAY (gdk_display_get_default ()), frame->xwindow);
}
