bgav_subtitle_stop(bgav_stream_t * s)
  {
  if(s->data.subtitle.cnv)
    {
    bgav_charset_converter_destroy(s->data.subtitle.cnv);
    s->data.subtitle.cnv = NULL;
    }
  if(s->data.subtitle.charset)
    {
    free(s->data.subtitle.charset);
    s->data.subtitle.charset = NULL;
    }
  if(s->data.subtitle.subreader)
    {
    bgav_subtitle_reader_stop(s);
    }
  if(s->data.subtitle.decoder)
    {
    s->data.subtitle.decoder->decoder->close(s);
    free(s->data.subtitle.decoder);
    s->data.subtitle.decoder = NULL;
    }

  }
