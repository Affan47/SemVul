test_incremental (gboolean line_break,
		  gint     length,
		  gsize   *encoded_length,
		  gsize   *decoded_length)
{
  char *p;
  gsize len, max, input_len, block_size;
  int state, save;
  guint decoder_save;

  data2 = g_malloc (length);
  text = g_malloc (length * 2);

  len = 0;
  state = 0;
  save = 0;
  input_len = 0;
  while (input_len < length)
    {
      block_size = MIN (BLOCK_SIZE, length - input_len);
      len += g_base64_encode_step (data + input_len, block_size,
				   line_break, text + len, &state, &save);
      input_len += block_size;
    }
  len += g_base64_encode_close (line_break, text + len, &state, &save);

  *encoded_length = len;

  if (line_break)
    max = length * 4 / 3 + length * 4 / (3 * 72) + 7;
  else
    max = length * 4 / 3 + 6;

  *decoded_length = 0;
  state = 0;
  decoder_save = 0;
  p = text;
  while (len > 0)
    {
      int chunk_len = MIN (BLOCK_SIZE, len);
      *decoded_length += g_base64_decode_step (p,
		      			       chunk_len,
					       data2 + *decoded_length,
					       &state, &decoder_save);
      p += chunk_len;
      len -= chunk_len;
    }
}
