stream_write_string (estream_t stream,
		     const unsigned char *string, u32 string_n)
{
  gpg_error_t err;

  err = stream_write_uint32 (stream, string_n);
  if (err)
    goto out;

  err = stream_write_data (stream, string, string_n);

 out:

  return err;
}
