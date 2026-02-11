evas_buffer_outbuf_buf_free_region_for_update(Outbuf *buf, RGBA_Image *update)
{
   if (update != buf->priv.back_buf)
     {
#ifdef EVAS_CSERVE2
        if (evas_cserve2_use_get())
          evas_cache2_image_close(&update->cache_entry);
        else
#endif
          evas_cache_image_drop(&update->cache_entry);
     }
}
