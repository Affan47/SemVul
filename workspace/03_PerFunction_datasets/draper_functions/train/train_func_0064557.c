bfd_compress_section_contents (bfd *abfd ATTRIBUTE_UNUSED,
			       sec_ptr sec ATTRIBUTE_UNUSED,
			       bfd_byte *uncompressed_buffer ATTRIBUTE_UNUSED,
			       bfd_size_type uncompressed_size ATTRIBUTE_UNUSED)
{
#ifndef HAVE_ZLIB_H
  bfd_set_error (bfd_error_invalid_operation);
  return FALSE;
#else
  uLong compressed_size;
  bfd_byte *compressed_buffer;

  compressed_size = compressBound (uncompressed_size) + 12;
  compressed_buffer = (bfd_byte *) bfd_malloc (compressed_size);

  if (compressed_buffer == NULL)
    return FALSE;

  if (compress ((Bytef*) compressed_buffer + 12,
		&compressed_size,
		(const Bytef*) uncompressed_buffer,
		uncompressed_size) != Z_OK)
    {
      free (compressed_buffer);
      bfd_set_error (bfd_error_bad_value);
      return FALSE;
    }


  memcpy (compressed_buffer, "ZLIB", 4);
  compressed_buffer[11] = uncompressed_size; uncompressed_size >>= 8;
  compressed_buffer[10] = uncompressed_size; uncompressed_size >>= 8;
  compressed_buffer[9] = uncompressed_size; uncompressed_size >>= 8;
  compressed_buffer[8] = uncompressed_size; uncompressed_size >>= 8;
  compressed_buffer[7] = uncompressed_size; uncompressed_size >>= 8;
  compressed_buffer[6] = uncompressed_size; uncompressed_size >>= 8;
  compressed_buffer[5] = uncompressed_size; uncompressed_size >>= 8;
  compressed_buffer[4] = uncompressed_size;
  compressed_size += 12;


  if (uncompressed_buffer == sec->contents)
    free (uncompressed_buffer);

  sec->contents = compressed_buffer;
  sec->size = compressed_size;
  sec->compress_status = COMPRESS_SECTION_DONE;

  return TRUE;
#endif
}
