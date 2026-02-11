mailimf_cache_field_write(MMAPString * mmapstr, size_t * indx,
				     struct mailimf_field * field)
{
  int r;

  r = mailimf_cache_int_write(mmapstr, indx, field->fld_type);
  if (r != MAIL_NO_ERROR)
    return r;

  switch (field->fld_type) {
  case MAILIMF_FIELD_ORIG_DATE:
    r = mailimf_cache_orig_date_write(mmapstr, indx,
        field->fld_data.fld_orig_date);
    break;
  case MAILIMF_FIELD_FROM:
    r = mailimf_cache_from_write(mmapstr, indx,
        field->fld_data.fld_from);
    break;
  case MAILIMF_FIELD_SENDER:
    r = mailimf_cache_sender_write(mmapstr, indx,
        field->fld_data.fld_sender);
    break;
  case MAILIMF_FIELD_REPLY_TO:
    r = mailimf_cache_reply_to_write(mmapstr, indx,
        field->fld_data.fld_reply_to);
    break;
  case MAILIMF_FIELD_TO:
    r = mailimf_cache_to_write(mmapstr, indx,
        field->fld_data.fld_to);
    break;
  case MAILIMF_FIELD_CC:
    r = mailimf_cache_cc_write(mmapstr, indx,
        field->fld_data.fld_cc);
    break;
  case MAILIMF_FIELD_BCC:
    r = mailimf_cache_bcc_write(mmapstr, indx,
        field->fld_data.fld_bcc);
    break;
  case MAILIMF_FIELD_MESSAGE_ID:
    r = mailimf_cache_message_id_write(mmapstr, indx,
        field->fld_data.fld_message_id);
    break;
  case MAILIMF_FIELD_IN_REPLY_TO:
    r = mailimf_cache_in_reply_to_write(mmapstr, indx,
        field->fld_data.fld_in_reply_to);
    break;
  case MAILIMF_FIELD_REFERENCES:
    r = mailimf_cache_references_write(mmapstr, indx,
        field->fld_data.fld_references);
    break;
  case MAILIMF_FIELD_SUBJECT:
    r = mailimf_cache_subject_write(mmapstr, indx,
        field->fld_data.fld_subject);
    break;
  default:
    r = 0;
    break;
  }

  if (r != MAIL_NO_ERROR)
    return r;

  return MAIL_NO_ERROR;
}
