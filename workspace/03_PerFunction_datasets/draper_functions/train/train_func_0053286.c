fs_comment_new (const char * name, const char * value)
{
  FishSoundComment * comment;

  if (!fs_comment_validate_byname (name)) return NULL;


  comment = fs_malloc (sizeof (FishSoundComment));
  if (comment == NULL) return NULL;

  comment->name = fs_strdup (name);
  if (comment->name == NULL) {
    fs_free (comment);
    return NULL;
  }

  if (value) {
    comment->value = fs_strdup (value);
    if (comment->value == NULL) {
      fs_free (comment->name);
      fs_free (comment);
      return NULL;
    }
  } else {
    comment->value = NULL;
  }

  return comment;
}
