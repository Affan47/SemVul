fetch_registered_part(struct mailprivacy * privacy,
    int (* fetch_section)(mailmessage *, struct mailmime *,
        char **, size_t *),
    struct mailmime * mime,
    char ** result, size_t * result_len)
{
  mailmessage * dummy_msg;
  int res;
  char * content;
  size_t content_len;
  int r;

  dummy_msg = mime_message_init(NULL);
  if (dummy_msg == NULL) {
    res = MAIL_ERROR_MEMORY;
    goto err;
  }

  r = mime_message_set_tmpdir(dummy_msg, privacy->tmp_dir);
  if (r != MAIL_NO_ERROR) {
    res = MAIL_ERROR_MEMORY;
    goto free_msg;
  }

  r = fetch_section(dummy_msg, mime, &content, &content_len);
  if (r != MAIL_NO_ERROR) {
    res = r;
    goto free_msg;
  }

  r = register_result_mmapstr(privacy, content);
  if (r != MAIL_NO_ERROR) {
    res = r;
    goto free_fetch;
  }

  mailmessage_free(dummy_msg);

  * result = content;
  * result_len = content_len;

  return MAIL_NO_ERROR;

 free_fetch:
  mailmessage_fetch_result_free(dummy_msg, content);
 free_msg:
  mailmessage_free(dummy_msg);
 err:
  return res;
}
