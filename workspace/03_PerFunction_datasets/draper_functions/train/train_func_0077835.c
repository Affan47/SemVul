random_string_from_available_chars (FT_Face face,
                                    gint n_chars)
{
  gchar *chars;
  gint idx, rand, total_chars;
  GString *retval;
  gchar *ptr, *end;

  idx = 0;
  chars = build_charlist_for_face (face, &total_chars);

  if (total_chars == 0)
    return NULL;

  retval = g_string_new (NULL);

  while (idx < n_chars) {
    rand = g_random_int_range (0, total_chars);

    ptr = g_utf8_offset_to_pointer (chars, rand);
    end = g_utf8_find_next_char (ptr, NULL);

    g_string_append_len (retval, ptr, end - ptr);
    idx++;
  }

  return g_string_free (retval, FALSE);
}
