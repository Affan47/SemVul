sshv2_buffer_get_int64 (gftp_request * request, sshv2_message * message,
                        unsigned int expected_response, int check_response,
#if G_HAVE_GINT64
                        guint64 * num)
{
  guint64 snum;
#else
                        guint32 * num)
{
  guint32 snum;
#endif
  guint32 hinum, lonum;
  int ret;

  if ((ret = sshv2_buffer_get_int32 (request, message, 0, 0, &hinum)) < 0)
    return (ret);

  if ((ret = sshv2_buffer_get_int32 (request, message, 0, 0, &lonum)) < 0)
    return (ret);

#if G_HAVE_GINT64
  snum = (gint64) lonum | ((gint64) hinum >> 32);
#else
  snum = lonum;
#endif

  if (check_response && snum != expected_response)
    return (sshv2_response_return_code (request, message, snum));

  if (num != NULL)
    *num = snum;

  return (0);
}
