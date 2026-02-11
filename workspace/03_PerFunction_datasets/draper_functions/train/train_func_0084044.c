soap_ctx_add_files(SoapCtx * ctx, attachments_t * attachments)
{
  part_t *part;
  char href[MAX_HREF_SIZE];

  if (attachments == NULL)
    return;

  part = attachments->parts;
  while (part)
  {
    soap_ctx_add_file(ctx, part->filename, part->content_type, href);
    part = part->next;
  }
}
