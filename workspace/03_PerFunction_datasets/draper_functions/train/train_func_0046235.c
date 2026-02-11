create_header (smtp_message_t message, const char *header,
               struct header_info *info)
{
  struct rfc2822_header *hdr;

  assert (message != NULL && header != NULL && info != NULL);

  if ((hdr = malloc (sizeof (struct rfc2822_header))) == NULL)
    return NULL;

  memset (hdr, 0, sizeof (struct rfc2822_header));
  hdr->header = strdup (header);
  hdr->info = info;
  info->hdr = hdr;
  APPEND_LIST (message->headers, message->end_headers, hdr);
  return hdr;
}
