process_header (smtp_message_t message, const char *header, int *len)
{
  const char *p;
  struct header_info *info;
  const struct header_actions *action;
  hdrprint_t print;

  assert (message != NULL && header != NULL && len != NULL);

  if (*len > 0
      && (p = memchr (header, ':', *len)) != NULL
      && (info = find_header (message, header, p - header)) != NULL)
    {
      if ((action = info->action) != NULL)
        {


          if (info->seen && !(action->flags & (MULTIPLE | PRESERVE)))
            header = NULL;
          if (info->prohibit || (action->flags & PROHIBIT))
            header = NULL;


	  if (header != NULL && info->override)
            {
	      if ((print = action->print) == NULL)
		print = print_string;
	      cat_reset (&message->hdr_buffer, 0);
	      (*print) (message, info->hdr);
	      header = cat_buffer (&message->hdr_buffer, len);
            }
        }
      else if (info->seen)
	header = NULL;
      info->seen = 1;
    }
  return header;
}
