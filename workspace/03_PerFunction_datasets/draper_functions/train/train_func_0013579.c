p_mtrace_pixbuf( GapPlayerMainGlobalParams *gpp
               , GdkPixbuf *pixbuf
              )
{
  if(gpp->mtrace_mode != GAP_PLAYER_MTRACE_OFF)
  {
    if(pixbuf)
    {
      gint32 nchannels;
      gint32 rowstride;
      gint32 width;
      gint32 height;
      guchar *pix_data;

      width = gdk_pixbuf_get_width(pixbuf);
      height = gdk_pixbuf_get_height(pixbuf);
      nchannels = gdk_pixbuf_get_n_channels(pixbuf);
      pix_data = gdk_pixbuf_get_pixels(pixbuf);
      rowstride = gdk_pixbuf_get_rowstride(pixbuf);

      p_mtrace_tmpbuf(gpp
                   , pix_data
                   , width
                   , height
                   , nchannels
                   );

    }
  }
}
