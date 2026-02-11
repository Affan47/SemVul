mailmime_field_free(struct mailmime_field * field)
{
  switch (field->fld_type) {
  case MAILMIME_FIELD_TYPE:
    if (field->fld_data.fld_content != NULL)
      mailmime_content_free(field->fld_data.fld_content);
    break;
  case MAILMIME_FIELD_TRANSFER_ENCODING:
    if (field->fld_data.fld_encoding != NULL)
      mailmime_encoding_free(field->fld_data.fld_encoding);
    break;
  case MAILMIME_FIELD_ID:
    if (field->fld_data.fld_id != NULL)
      mailmime_id_free(field->fld_data.fld_id);
    break;
  case MAILMIME_FIELD_DESCRIPTION:
    if (field->fld_data.fld_description != NULL)
      mailmime_description_free(field->fld_data.fld_description);
    break;
  case MAILMIME_FIELD_DISPOSITION:
    if (field->fld_data.fld_disposition != NULL)
      mailmime_disposition_free(field->fld_data.fld_disposition);
    break;
  case MAILMIME_FIELD_LANGUAGE:
    if (field->fld_data.fld_language != NULL)
      mailmime_language_free(field->fld_data.fld_language);
    break;
  }

  free(field);
}
