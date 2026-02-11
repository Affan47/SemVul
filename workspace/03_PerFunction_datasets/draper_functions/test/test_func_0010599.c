ndmbstf_next (
  FILE *fp,
  char *key,
  char *buf,
  unsigned max_buf)
{
	int		rc, buf_len;


	buf_len = ndmbstf_getline (fp, buf, max_buf);

	if (buf_len <= 0) {
		if (buf_len == EOF)
			return EOF;
		return -2;
	}

	rc = ndmbstf_compare (key, buf);
	if (rc == 0) {

		return buf_len;
	} else {
		return 0;
	}
}
