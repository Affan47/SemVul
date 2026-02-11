FIID_TEMPLATE_FIELD_LOOKUP (fiid_template_t tmpl,
                            const char *field)
{
  int ret;

  if ((ret = fiid_template_field_lookup (tmpl, field)) < 0)
    return (ret);

  if (!ret)
    {
      errno = EINVAL;
      return (-1);
    }

  return (ret);
}
