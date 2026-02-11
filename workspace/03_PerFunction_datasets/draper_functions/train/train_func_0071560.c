build_body_file(char * filename)
{
  struct mailmime_fields * mime_fields;
  struct mailmime * mime_sub;
  struct mailmime_content * content;
  struct mailmime_parameter * param;
  char * dup_filename;
  int r;


  dup_filename = strdup(filename);
  if (dup_filename == NULL)
    goto err;

  mime_fields =
    mailmime_fields_new_filename(MAILMIME_DISPOSITION_TYPE_ATTACHMENT,
        dup_filename, MAILMIME_MECHANISM_BASE64);
  if (mime_fields == NULL)
    goto free_dup_filename;

  content = mailmime_content_new_with_str("text/plain");
  if (content == NULL) {
    goto free_fields;
  }

  param = mailmime_param_new_with_data("charset", DEST_CHARSET);
  if (param == NULL) {
    goto free_content;
  }

  r = clist_append(content->ct_parameters, param);
  if (r < 0) {
    mailmime_parameter_free(param);
    goto free_content;
  }

  mime_sub = mailmime_new_empty(content, mime_fields);
  if (mime_sub == NULL) {
    goto free_content;
  }

  dup_filename = strdup(filename);
  if (dup_filename == NULL)
    goto free_mime;

  r = mailmime_set_body_file(mime_sub, dup_filename);
  if (r != MAILIMF_NO_ERROR) {
    goto free_mime;
  }

  return mime_sub;

 free_mime:
  mailmime_free(mime_sub);
  goto err;
 free_content:
  mailmime_content_free(content);
 free_fields:
  mailmime_fields_free(mime_fields);
  goto err;
 free_dup_filename:
  free(dup_filename);
 err:
  return NULL;
}
