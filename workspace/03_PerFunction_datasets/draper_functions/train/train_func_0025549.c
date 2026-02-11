mailmime_add_part(struct mailmime * build_info,
		      struct mailmime * part)
{
  int r;

  if (build_info->mm_type == MAILMIME_MESSAGE) {
    build_info->mm_data.mm_message.mm_msg_mime = part;
    part->mm_parent_type = MAILMIME_MESSAGE;
    part->mm_parent = build_info;
  }
  else if (build_info->mm_type == MAILMIME_MULTIPLE) {
    r = clist_append(build_info->mm_data.mm_multipart.mm_mp_list, part);
    if (r != 0)
      return MAILIMF_ERROR_MEMORY;

    part->mm_parent_type = MAILMIME_MULTIPLE;
    part->mm_parent = build_info;
    part->mm_multipart_pos =
      clist_end(build_info->mm_data.mm_multipart.mm_mp_list);
  }
  else {
    return MAILIMF_ERROR_INVAL;
  }
  return MAILIMF_NO_ERROR;
}
