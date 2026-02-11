fiid_template_len_bytes (fiid_template_t tmpl)
{
  int len;

  if (!tmpl)
    {

      errno = EINVAL;
      return (-1);
    }

  if ((len = fiid_template_len (tmpl)) < 0)
    return (-1);

  if (len % 8)
    {

      errno = EINVAL;
      return (-1);
    }

  return (BITS_ROUND_BYTES (len));
}
