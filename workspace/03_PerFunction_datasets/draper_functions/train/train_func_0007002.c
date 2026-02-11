send_key_data (ctrl_t ctrl, const char *name,
               const unsigned char *a, size_t alen)
{
  char *buffer, *buf;
  size_t buflen;

  buffer = buf = bin2hex (a, alen, NULL);
  if (!buffer)
    {
      log_error ("memory allocation error in send_key_data\n");
      return;
    }
  buflen = strlen (buffer);


  for ( ;buflen > 768; buflen -= 768, buf += 768)
    send_status_info (ctrl, "KEY-DATA",
                      "-", 1,
                      buf, 768,
                      NULL, 0);
  send_status_info (ctrl, "KEY-DATA",
                    name, (size_t)strlen(name),
                    buf, buflen,
                    NULL, 0);
  xfree (buffer);
}
