maildir_message_get(struct maildir * md, const char * uid)
{
  chashdatum key;
  chashdatum value;
  char filename[PATH_MAX];
  char * dup_filename;
  struct maildir_msg * msg;
  char * dir;
  int r;

  key.data = (void *) uid;
  key.len = strlen(uid);
  r = chash_get(md->mdir_msg_hash, &key, &value);
  if (r < 0)
    return NULL;

  msg = value.data;
  if ((msg->msg_flags & MAILDIR_FLAG_NEW) != 0)
    dir = "new";
  else
    dir = "cur";

  snprintf(filename, sizeof(filename), "%s/%s/%s",
      md->mdir_path, dir, msg->msg_filename);

  dup_filename = strdup(filename);
  if (dup_filename == NULL)
    return NULL;

  return dup_filename;
}
