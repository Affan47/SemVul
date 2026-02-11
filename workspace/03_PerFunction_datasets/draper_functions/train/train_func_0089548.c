lvl_save_body_file (int fd, const a_level *out)
{
  ssize_t length = out->tile_count * LVL_RECORD_SIZE;
  a_u8 *data = xmalloc (length);
  memset (data, 0, length);

  encode_level_body (data, out);

  if (write (fd, data, length) != length) {
    free (data);
    return -1;
  }

  free (data);
  return 0;
}
