sshv2_buffer_get_string (gftp_request * request, sshv2_message * message,
                         int return_string)
{
  guint32 len, buflen;
  char *string;

  if (sshv2_buffer_get_int32 (request, message, 0, 0, &len) < 0)
    return (NULL);

  buflen = message->end - message->pos;
  if (len > SSH_MAX_STRING_SIZE || (buflen < len))
    {
      sshv2_wrong_response (request, message);
      return (NULL);
    }

  if (return_string)
    {
      string = g_malloc0 (len + 1);
      memcpy (string, message->pos, len);
      string[len] = '\0';
    }
  else
    string = NULL;

  message->pos += len;
  return (string);
}
