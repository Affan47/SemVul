open_dvd(bgav_input_context_t * ctx, const char * url, char ** r)
  {
  int i, j;
  dvd_t * priv;
  tt_srpt_t *ttsrpt;
  char volid[32];
  unsigned char volsetid[128];
#ifdef HAVE_CDIO
  driver_return_code_t err;
#endif
  int is_image = 0;

  const char * pos;

  pos = strrchr(url, '/');
  if(pos && !strcasecmp(pos, "/video_ts"))
    is_image = 1;

  priv = calloc(1, sizeof(*priv));

  ctx->priv = priv;


  if(!is_image)
    {
#ifdef HAVE_CDIO
    if((err = cdio_close_tray(url, NULL)))
#if LIBCDIO_VERSION_NUM >= 77
      bgav_log(ctx->opt, BGAV_LOG_ERROR, LOG_DOMAIN,
               "cdio_close_tray failed: %s",
              cdio_driver_errmsg(err));
#else
    bgav_log(ctx->opt, BGAV_LOG_ERROR, LOG_DOMAIN,
             "cdio_close_tray failed");
#endif

#else
    return 0;
#endif
    }


  priv->dvd_reader = DVDOpen(url);
  if(!priv->dvd_reader)
    {
    bgav_log(ctx->opt, BGAV_LOG_ERROR, LOG_DOMAIN, "DVDOpen failed");
    return 0;
    }


  if(!DVDUDFVolumeInfo(priv->dvd_reader, volid, 32,
                      volsetid, 128))
    {
    ctx->disc_name = bgav_strdup(volid);
    }


  priv->vmg_ifo = ifoOpen(priv->dvd_reader, 0);
  if(!priv->vmg_ifo)
    {
    bgav_log(ctx->opt, BGAV_LOG_ERROR, LOG_DOMAIN, "ifoOpen failed");
    return 0;
    }
#if 0
  dump_vmg_ifo(priv->vmg_ifo);
#endif
  ttsrpt = priv->vmg_ifo->tt_srpt;


  ctx->tt = bgav_track_table_create(0);

  for(i = 0; i < ttsrpt->nr_of_srpts; i++)
    {
    for(j = 0; j < ttsrpt->title[i].nr_of_angles; j++)
      {
#if 0
      if(ctx->opt->dvd_chapters_as_tracks)
        {

        for(k = 0; k < ttsrpt->title[i].nr_of_ptts; k++)
          setup_track(ctx, i, k, j);
        }
      else
        {
#endif

        setup_track(ctx, i, 0, j);
#if 0
        }
#endif
      }
    }


  ctx->demuxer = bgav_demuxer_create(ctx->opt, &bgav_demuxer_mpegps, ctx);
  ctx->demuxer->tt = ctx->tt;


  ctx->demuxer->flags |= BGAV_DEMUXER_CAN_SEEK;

  ctx->sector_size        = 2048;
  ctx->sector_size_raw    = 2048;
  ctx->sector_header_size = 0;
  ctx->can_pause = 1;

  return 1;
  }
