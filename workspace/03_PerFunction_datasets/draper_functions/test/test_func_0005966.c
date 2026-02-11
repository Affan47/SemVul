gap_player_cache_new_data(guchar *th_data
                         , gint32 th_size
                         , gint32 th_width
                         , gint32 th_height
                         , gint32 th_bpp
                         , GapPlayerCacheCompressionType compression
                         , gint32 flip_status
                         )
{
  GapPlayerCacheData* cdata;

  cdata = g_new ( GapPlayerCacheData, 1 );
  cdata->compression = compression;
  cdata->th_data_size = th_size;
  cdata->th_width = th_width;
  cdata->th_height = th_height;
  cdata->th_bpp = th_bpp;
  cdata->flip_status = flip_status;
  if (compression == GAP_PLAYER_CACHE_COMPRESSION_NONE)
  {
    cdata->th_data = th_data;

  }
  else
  {
    printf("** ERROR: player chache compression not implemented yet.\n");
    cdata->compression = GAP_PLAYER_CACHE_COMPRESSION_NONE;
    cdata->th_data = th_data;
  }

  return (cdata);
}
