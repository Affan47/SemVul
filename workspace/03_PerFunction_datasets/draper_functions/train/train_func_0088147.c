gftp_config_file_write_text (gftp_config_vars * cv, char *buf, size_t buflen,
                             int to_config_file)
{
  char *outstr;

  if (cv->value != NULL)
    {
      outstr = cv->value;
      g_snprintf (buf, buflen, "%s", outstr);
      return (0);
    }
  else
    return (-1);
}
