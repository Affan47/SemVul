p_frame_chache_processing(GapPlayerMainGlobalParams *gpp
    , const gchar *ckey)
{
  GapPlayerCacheData *cdata;
  guchar             *th_data;
  gint32              th_size;
  gint32              th_width;
  gint32              th_height;
  gint32              th_bpp;
  gboolean            th_has_alpha;


  if (gpp->max_player_cache <= 0)
  {

    return;
  }
  if(gap_player_cache_lookup(ckey) != NULL)
  {

    return;
  }

  th_data = gap_pview_get_repaint_thdata(gpp->pv_ptr
                            , &th_size
                            , &th_width
                            , &th_height
                            , &th_bpp
                            , &th_has_alpha
                            );
  if (th_data != NULL)
  {
    cdata = gap_player_cache_new_data(th_data
             , th_size
             , th_width
             , th_height
             , th_bpp
             , gpp->cache_compression
             , gpp->pv_ptr->flip_status
             );
    if(cdata != NULL)
    {


      gap_player_cache_insert(ckey, cdata);
      p_update_cache_status(gpp);
    }
  }

}
