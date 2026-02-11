generate_key_from_section(char * key, size_t size,
				      mailmessage * msg_info,
				      struct mailmime * mime, int type)
{
  char section_str[PATH_MAX];

  generate_key_from_mime_section(section_str, PATH_MAX, mime);

  switch (type) {
  case IMAP_SECTION_MESSAGE:
    snprintf(key, size, "%s-%s", msg_info->msg_uid, section_str);
    break;
  case IMAP_SECTION_HEADER:
    snprintf(key, size, "%s-%s-header", msg_info->msg_uid, section_str);
    break;
  case IMAP_SECTION_MIME:
    snprintf(key, size, "%s-%s-mime", msg_info->msg_uid, section_str);
    break;
  case IMAP_SECTION_BODY:
    snprintf(key, size, "%s-%s-text", msg_info->msg_uid, section_str);
    break;
  }
}
