taf_decompress (sc_tafref_t taf, sc_read_callbackref_t callback,
                void *opaque, sc_bool is_gamefile)
{
  sc_byte *in_buffer, *out_buffer;
  z_stream stream;
  sc_int status;
  sc_bool is_first_block;


  in_buffer = sc_malloc (IN_BUFFER_SIZE);
  out_buffer = sc_malloc (OUT_BUFFER_SIZE);


  stream.next_out = out_buffer;
  stream.avail_out = OUT_BUFFER_SIZE;
  stream.next_in = in_buffer;
  stream.avail_in = 0;

  stream.zalloc = Z_NULL;
  stream.zfree = Z_NULL;
  stream.opaque = Z_NULL;

  status = inflateInit (&stream);
  if (status != Z_OK)
    {
      sc_error ("taf_decompress: inflateInit: error %ld\n", status);
      sc_free (in_buffer);
      sc_free (out_buffer);
      return FALSE;
    }


  is_first_block = TRUE;


  while (TRUE)
    {
      sc_int in_bytes, out_bytes;


      if (stream.avail_in == 0)
        {
          in_bytes = callback (opaque, in_buffer, IN_BUFFER_SIZE);
          stream.next_in = in_buffer;
          stream.avail_in = in_bytes;
        }


      status = inflate (&stream, Z_SYNC_FLUSH);
      if (status != Z_STREAM_END && status != Z_OK)
        {
          if (is_gamefile || !is_first_block)
            sc_error ("taf_decompress: inflate: error %ld\n", status);
          sc_free (in_buffer);
          sc_free (out_buffer);
          return FALSE;
        }
      out_bytes = OUT_BUFFER_SIZE - stream.avail_out;


      if (out_bytes > 0)
        {
          sc_int consumed;


          consumed = taf_append_buffer (taf, out_buffer, out_bytes);


          memmove (out_buffer,
                   out_buffer + consumed, OUT_BUFFER_SIZE - consumed);


          stream.next_out = out_buffer + out_bytes - consumed;
          stream.avail_out += consumed;
        }


      is_first_block = FALSE;


      if (status == Z_STREAM_END && stream.avail_out == OUT_BUFFER_SIZE)
        break;
    }


  taf->total_in_bytes = stream.total_in;
  if (is_gamefile)
    taf->total_in_bytes += VERSION_HEADER_SIZE + V400_HEADER_EXTRA;


  status = inflateEnd (&stream);
  if (status != Z_OK)
    sc_error ("taf_decompress: warning: inflateEnd: error %ld\n", status);

  if (taf->is_unterminated)
    sc_fatal ("taf_decompress: unterminated final data slab\n");


  sc_free (in_buffer);
  sc_free (out_buffer);
  return TRUE;
}
