bgav_qt_minf_free(qt_minf_t * h)
  {


  bgav_qt_hdlr_free(&h->hdlr);
  bgav_qt_stbl_free(&h->stbl);

  if(h->has_dinf)
    bgav_qt_dinf_free(&h->dinf);

  if(h->has_gmhd)
    bgav_qt_gmhd_free(&h->gmhd);
  }
