close_http(bgav_input_context_t * ctx)
  {
  http_priv * p = ctx->priv;

  if(p->chunk_buffer)
    free(p->chunk_buffer);
  bgav_http_close(p->h);
  if(p->charset_cnv)
    bgav_charset_converter_destroy(p->charset_cnv);
  free(p);
  }
