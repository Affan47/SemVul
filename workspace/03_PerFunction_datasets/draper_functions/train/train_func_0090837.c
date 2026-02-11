get_first_from_addr(struct mailmime * mime)
{
  clistiter * cur;
  struct mailimf_single_fields single_fields;
  struct mailimf_fields * fields;
  struct mailimf_mailbox * mb;

  if (mime->mm_type != MAILMIME_MESSAGE)
    return NULL;

  fields = mime->mm_data.mm_message.mm_fields;
  if (fields == NULL)
    return NULL;

  mailimf_single_fields_init(&single_fields, fields);

  if (single_fields.fld_from == NULL)
    return NULL;

  cur = clist_begin(single_fields.fld_from->frm_mb_list->mb_list);
  if (cur == NULL)
    return NULL;

  mb = clist_content(cur);

  return mb->mb_addr_spec;
}
