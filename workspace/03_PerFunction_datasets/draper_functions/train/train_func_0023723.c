mailmime_fields_new_with_data(struct mailmime_mechanism * encoding,
			      char * id,
			      char * description,
			      struct mailmime_disposition * disposition,
			      struct mailmime_language * language)
{
  struct mailmime_field * field;
  struct mailmime_fields * fields;
  int r;

  fields = mailmime_fields_new_empty();
  if (fields == NULL)
    goto err;

#if 0
  if (content != NULL) {
    field = mailmime_field_new(MAILMIME_FIELD_TYPE,
			       content, NULL, NULL, NULL, 0, NULL, NULL);
    if (field == NULL)
      goto free;

    r = mailmime_fields_add(fields, field);
    if (r != MAILIMF_NO_ERROR) {
      mailmime_field_detach(field);
      mailmime_field_free(field);
      goto free;
    }
  }
#endif

  if (encoding != NULL) {
    field = mailmime_field_new(MAILMIME_FIELD_TRANSFER_ENCODING,
			       NULL, encoding, NULL, NULL, 0, NULL, NULL);
    if (field == NULL)
      goto free;

    r = mailmime_fields_add(fields, field);
    if (r != MAILIMF_NO_ERROR) {
      mailmime_field_detach(field);
      mailmime_field_free(field);
      goto free;
    }
  }

  if (id != NULL) {
    field = mailmime_field_new(MAILMIME_FIELD_ID,
			       NULL, NULL, id, NULL, 0, NULL, NULL);
    if (field == NULL)
      goto free;

    r = mailmime_fields_add(fields, field);
    if (r != MAILIMF_NO_ERROR) {
      mailmime_field_detach(field);
      mailmime_field_free(field);
      goto free;
    }
  }

  if (description != NULL) {
    field = mailmime_field_new(MAILMIME_FIELD_DESCRIPTION,
			       NULL, NULL, NULL, description, 0, NULL, NULL);
    if (field == NULL)
      goto free;

    r = mailmime_fields_add(fields, field);
    if (r != MAILIMF_NO_ERROR) {
      mailmime_field_detach(field);
      mailmime_field_free(field);
      goto free;
    }
  }

  if (disposition != NULL) {
    field = mailmime_field_new(MAILMIME_FIELD_DISPOSITION,
			       NULL, NULL, NULL, NULL, 0, disposition, NULL);
    if (field == NULL)
      goto free;

    r = mailmime_fields_add(fields, field);
    if (r != MAILIMF_NO_ERROR) {
      mailmime_field_detach(field);
      mailmime_field_free(field);
      goto free;
    }
  }

  if (language != NULL) {
    field = mailmime_field_new(MAILMIME_FIELD_DISPOSITION,
			       NULL, NULL, NULL, NULL, 0, NULL, language);
    if (field == NULL)
      goto free;

    r = mailmime_fields_add(fields, field);
    if (r != MAILIMF_NO_ERROR) {
      mailmime_field_detach(field);
      mailmime_field_free(field);
      goto free;
    }
  }

  return fields;

 free:
  clist_foreach(fields->fld_list, (clist_func) mailmime_field_detach, NULL);
  mailmime_fields_free(fields);
 err:
  return NULL;
}
