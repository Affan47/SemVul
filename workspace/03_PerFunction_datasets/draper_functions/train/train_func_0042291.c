scm_i_substring_copy (SCM str, size_t start, size_t end)
{
  size_t len = end - start;
  SCM buf, my_buf;
  size_t str_start;
  get_str_buf_start (&str, &buf, &str_start);
  my_buf = make_stringbuf (len);
  memcpy (STRINGBUF_CHARS (my_buf),
	  STRINGBUF_CHARS (buf) + str_start + start, len);
  scm_remember_upto_here_1 (buf);
  return scm_double_cell (STRING_TAG, SCM_UNPACK(my_buf),
			  (scm_t_bits)0, (scm_t_bits) len);
}
