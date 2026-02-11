uncompress_section_contents (unsigned char **buffer ATTRIBUTE_UNUSED,
			     dwarf_size_type *size ATTRIBUTE_UNUSED)
{
#ifndef HAVE_ZLIB_H
  return FALSE;
#else
  dwarf_size_type compressed_size = *size;
  unsigned char * compressed_buffer = *buffer;
  dwarf_size_type uncompressed_size;
  unsigned char * uncompressed_buffer;
  z_stream strm;
  int rc;
  dwarf_size_type header_size = 12;


  if (compressed_size < header_size
      || ! streq ((char *) compressed_buffer, "ZLIB"))
    return 0;

  uncompressed_size = compressed_buffer[4]; uncompressed_size <<= 8;
  uncompressed_size += compressed_buffer[5]; uncompressed_size <<= 8;
  uncompressed_size += compressed_buffer[6]; uncompressed_size <<= 8;
  uncompressed_size += compressed_buffer[7]; uncompressed_size <<= 8;
  uncompressed_size += compressed_buffer[8]; uncompressed_size <<= 8;
  uncompressed_size += compressed_buffer[9]; uncompressed_size <<= 8;
  uncompressed_size += compressed_buffer[10]; uncompressed_size <<= 8;
  uncompressed_size += compressed_buffer[11];


  strm.zalloc = NULL;
  strm.zfree = NULL;
  strm.opaque = NULL;
  strm.avail_in = compressed_size - header_size;
  strm.next_in = (Bytef *) compressed_buffer + header_size;
  strm.avail_out = uncompressed_size;
  uncompressed_buffer = (unsigned char *) xmalloc (uncompressed_size);

  rc = inflateInit (& strm);
  while (strm.avail_in > 0)
    {
      if (rc != Z_OK)
        goto fail;
      strm.next_out = ((Bytef *) uncompressed_buffer
                       + (uncompressed_size - strm.avail_out));
      rc = inflate (&strm, Z_FINISH);
      if (rc != Z_STREAM_END)
        goto fail;
      rc = inflateReset (& strm);
    }
  rc = inflateEnd (& strm);
  if (rc != Z_OK
      || strm.avail_out != 0)
    goto fail;

  free (compressed_buffer);
  *buffer = uncompressed_buffer;
  *size = uncompressed_size;
  return 1;

 fail:
  free (uncompressed_buffer);

  *buffer = NULL;
  return 0;
#endif
}
