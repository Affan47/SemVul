other_to_UTF(const char *buf, int buf_len)
{
   size_t rc;
   char *outbuf;
   gsize bytes_read;
   GError *err = NULL;
   size_t str_len;

#ifdef OTHERCONV_DEBUG
   jp_logf(JP_LOG_DEBUG, "%s:%s reset iconv state...\n", __FILE__, __FUNCTION__);
#endif
   rc = g_iconv(glob_frompda, NULL, NULL, NULL, NULL);
#ifdef OTHERCONV_DEBUG
   jp_logf(JP_LOG_DEBUG, "%s:%s converting   [%s]\n", __FILE__, __FUNCTION__, buf);
#endif

   if (buf_len == -1) {
      str_len = -1;
   } else {
      str_len = oc_strnlen(buf, buf_len-1);
   }

   outbuf = (char *)g_convert_with_iconv((gchar *)buf,
            str_len, glob_frompda, &bytes_read, NULL, &err);

   if (err != NULL) {
      char c;
      char *head, *tail;
      int  outbuf_len;
      char *tmp_buf = (char *)buf;
      static int call_depth = 0;
      printf("ERROR HAPPENED\n");
      if (0 == call_depth)
         jp_logf(JP_LOG_WARN, _("%s:%s g_convert_with_iconv error: %s, buff: %s\n"),
                              __FILE__, __FUNCTION__,
                              err ? err->message : _("last char truncated"),
                              buf);
      if (err != NULL)
         g_error_free(err);
      else
         g_free(outbuf);

      if (buf_len == -1) {
         buf_len = strlen(buf);
      }


      c = tmp_buf[bytes_read];
      tmp_buf[bytes_read] = '\0';
      head = g_convert_with_iconv(tmp_buf,
                                  oc_strnlen(tmp_buf, buf_len),
                                  glob_frompda,
                                  &bytes_read,
                                  NULL, NULL);
      tmp_buf[bytes_read] = c;

      call_depth++;
      tail = other_to_UTF(tmp_buf + bytes_read +1, buf_len - bytes_read - 1);
      call_depth--;

      outbuf_len = strlen(head) +4 + strlen(tail)+1;
      outbuf = g_malloc(outbuf_len);
      g_snprintf(outbuf, outbuf_len, "%s\\%02X%s", head, (unsigned char)c, tail);

      g_free(head);
      g_free(tail);
   }

#ifdef OTHERCONV_DEBUG
   jp_logf(JP_LOG_DEBUG, "%s:%s converted to [%s]\n", __FILE__, __FUNCTION__, outbuf);
#endif


   return outbuf;
}
