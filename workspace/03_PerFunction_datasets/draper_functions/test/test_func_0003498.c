maildir_message_remove(struct maildir * md, const char * uid)
{
  chashdatum key;
  chashdatum value;
  char filename[PATH_MAX];
  struct maildir_msg * msg;
  char * dir;
  int r;
  int res;

  key.data = (void *) uid;
  key.len = strlen(uid);
  r = chash_get(md->mdir_msg_hash, &key, &value);
  if (r < 0) {
    res = MAILDIR_ERROR_NOT_FOUND;
    goto err;
  }

  msg = value.data;
  if ((msg->msg_flags & MAILDIR_FLAG_NEW) != 0)
    dir = "new";
  else
    dir = "cur";

  snprintf(filename, sizeof(filename), "%s/%s/%s",
      md->mdir_path, dir, msg->msg_filename);

  r = unlink(filename);
  if (r < 0) {
    res = MAILDIR_ERROR_FILE;
    goto err;
  }

  return MAILDIR_NO_ERROR;

 err:
  return res;
}
