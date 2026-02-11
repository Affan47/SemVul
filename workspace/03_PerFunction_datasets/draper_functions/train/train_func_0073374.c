_getKey(const gchar *buf, gchar **key, gchar **tag, guint iLine, GError **error)
{
  gchar *key_, *tag_, *end, *ret;

  *key = (gchar*)0;
  *tag = (gchar*)0;

  ret = strchr(buf, ':');
  if (!ret)
    return (gchar*)0;

  key_ = g_strndup(buf, ret - buf);
  key_ = g_strstrip(key_);
  *key = key_;


  tag_ = strchr(key_, '[');
  if (tag_)
    {
      *tag_ = '\0';
      tag_ += 1;
      end = strchr(tag_, ']');
      if (end)
        {
          *end = '\0';
          tag_ = g_strdup(tag_);
          *tag = tag_;
        }
      else
        *error = g_error_new(TOOL_CONFIG_FILE_ERROR, TOOL_CONFIG_FILE_ERROR_TAG,
                             _("Parse error at line %d,"
                               " the tag '%s' is not closed.\n"),
                             iLine, tag_);
    }

  DBG_fprintf(stderr,"Visu ConfigFile: read a flag (tag): '%s' (%s).\n", key_, tag_);
  return ret;
}
