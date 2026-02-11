fiid_template_len (fiid_template_t tmpl)
{
  unsigned int temp;
  int len = 0;

  if (!tmpl)
    {

      errno = EINVAL;
      return (-1);
    }

  if ((len = _fiid_template_len (tmpl,
                                 &temp)) < 0)
    return (-1);

  return (len);
}
