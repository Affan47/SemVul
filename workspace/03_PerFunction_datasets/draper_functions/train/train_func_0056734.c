mhdriver_move_message(mailsession * session,
				 uint32_t num, const char * mb)
{
  int r;
  struct mailmh_folder * src_folder;
  struct mailmh_folder * dest_folder;
  struct mailmh * mh;

  mh = get_mh_session(session);
  if (mh == NULL)
    return MAIL_ERROR_BAD_STATE;

  src_folder = get_mh_cur_folder(session);
  if (src_folder == NULL)
    return MAIL_ERROR_BAD_STATE;

  dest_folder = mailmh_folder_find(mh->mh_main, mb);
  if (dest_folder == NULL)
    return MAIL_ERROR_FOLDER_NOT_FOUND;

  r = mailmh_folder_move_message(dest_folder, src_folder, num);

  return mhdriver_mh_error_to_mail_error(r);
}
