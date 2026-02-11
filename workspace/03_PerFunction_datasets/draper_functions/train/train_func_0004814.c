fs_strdup_len (const char * s, size_t len)
{
  char * ret;
  if (s == NULL) return NULL;
  if (len == 0) return NULL;
  len = fs_comment_clamp(len);
  ret = fs_malloc (len + 1);
  if (ret == NULL) return NULL;
  if (strncpy (ret, s, len) == NULL) {
    fs_free (ret);
    return NULL;
  }

  ret[len] = '\0';
  return ret;
}
