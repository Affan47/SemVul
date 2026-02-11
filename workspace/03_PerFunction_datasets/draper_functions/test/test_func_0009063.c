http_close (http_t hd, int keep_read_stream)
{
  if (!hd)
    return;
  if (!hd->fp_read && !hd->fp_write && hd->sock != -1)
    sock_close (hd->sock);
  if (hd->fp_read && !keep_read_stream)
    P_ES(fclose) (hd->fp_read);
  if (hd->fp_write)
    P_ES(fclose) (hd->fp_write);
  http_release_parsed_uri (hd->uri);
  while (hd->headers)
    {
      header_t tmp = hd->headers->next;
      xfree (hd->headers->value);
      xfree (hd->headers);
      hd->headers = tmp;
    }
  xfree (hd->buffer);
  xfree (hd);
}
