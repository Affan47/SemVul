id3v2_genre_fields_to_taglist (ID3TagsWorking * work, const gchar * tag_name,
    GArray * tag_fields)
{
  gchar *tag_str = NULL;
  gboolean result = FALSE;
  gint i;

  for (i = 0; i < tag_fields->len; i++) {
    gint len;

    tag_str = g_array_index (tag_fields, gchar *, i);
    if (tag_str == NULL)
      continue;

    len = strlen (tag_str);


    if (TRUE || work->hdr.version <= 0x300) {


      while (len >= 2) {
        gint pos;
        gboolean found = FALSE;


        if (tag_str[0] == '(' && tag_str[1] == '(') {
          tag_str++;
          len--;
          break;
        }


        if (tag_str[0] != '(')
          break;

        for (pos = 1; pos < len; pos++) {
          if (tag_str[pos] == ')') {
            gchar *tmp_str;

            tmp_str = g_strndup (tag_str + 1, pos - 1);
            result |=
                id3v2_genre_string_to_taglist (work, tag_name, tmp_str,
                pos - 1);
            g_free (tmp_str);
            tag_str += pos + 1;
            len -= pos + 1;
            found = TRUE;
            break;
          }


          if (!g_ascii_isdigit (tag_str[pos]))
            break;
        }
        if (!found)
          break;
      }
    }

    if (len > 0 && tag_str != NULL)
      result |= id3v2_genre_string_to_taglist (work, tag_name, tag_str, len);
  }
  return result;
}
