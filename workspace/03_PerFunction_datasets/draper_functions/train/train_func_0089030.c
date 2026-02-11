show_part_info(FILE * f,
    struct mailmime_single_fields * mime_fields,
    struct mailmime_content * content)
{
  char * description;
  char * filename;
  int col;
  int r;

  description = mime_fields->fld_description;
  filename = mime_fields->fld_disposition_filename;

  col = 0;

  r = fprintf(f, " [ Part ");
  if (r < 0)
    goto err;

  if (content != NULL) {
    r = mailmime_content_type_write(f, &col, content);
    if (r != MAILIMF_NO_ERROR)
      goto err;
  }

  if (filename != NULL) {
    r = fprintf(f, " (%s)", filename);
    if (r < 0)
      goto err;
  }

  if (description != NULL) {
    r = fprintf(f, " : %s", description);
    if (r < 0)
      goto err;
  }

  r = fprintf(f, " ]\n\n");
  if (r < 0)
    goto err;

  return NO_ERROR;

 err:
  return ERROR_FILE;
}
