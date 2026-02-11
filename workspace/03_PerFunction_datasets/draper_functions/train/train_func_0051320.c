mailprivacy_msg_fetch_section_header(struct mailprivacy * privacy,
    mailmessage * msg_info,
    struct mailmime * mime,
    char ** result,
    size_t * result_len)
{
  if (msg_is_modified(privacy, msg_info) &&
      mime_is_registered(privacy, mime)) {
    return fetch_registered_part(privacy, mailmessage_fetch_section_header,
        mime, result, result_len);
  }

  return mailmessage_fetch_section_header(msg_info, mime, result, result_len);
}
