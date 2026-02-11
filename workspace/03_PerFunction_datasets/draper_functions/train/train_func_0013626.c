inf_text_chunk_get_segment(InfTextChunk* self,
                           guint pos,
                           gsize* index)
{
  InfTextChunkSegment* found;
  InfTextChunkSegment key;
  GSequenceIter* iter;

  GIConv cd;
  gchar buffer[4];

  gchar* inbuf;
  gchar* outbuf;
  gsize inlen;
  gsize outlen;
  guint count;
  gsize result;

  g_assert(pos <= self->length);


  key.offset = pos;


  iter = g_sequence_search(
    self->segments,
    &key,
    inf_text_chunk_segment_cmp,
    NULL
  );

  if(self->length > 0)
  {
    g_assert(iter != g_sequence_get_begin_iter(self->segments));

    iter = g_sequence_iter_prev(iter);
    found = g_sequence_get(iter);

    g_assert(pos >= found->offset);


    g_assert(pos <= inf_text_chunk_next_offset(self, iter));


    if(index != NULL)
    {
      if(pos == inf_text_chunk_next_offset(self, iter))
      {
        *index = found->length;
      }
      else
      {


        cd = g_iconv_open("UCS-4", g_quark_to_string(self->encoding));
        g_assert(cd != (GIConv)-1);

        inbuf = found->text;
        inlen = found->length;

        for(count = 0; count < pos - found->offset; ++ count)
        {
          g_assert(inlen > 0);

          outbuf = buffer;
          outlen = 4;

          result = g_iconv(cd, &inbuf, &inlen, &outbuf, &outlen);
          g_assert(result == (size_t)(-1));
        }

        g_iconv_close(cd);
        *index = found->length - inlen;
      }
    }
  }
  else
  {
    if(*index)
      *index = 0;
  }

  return iter;
}
