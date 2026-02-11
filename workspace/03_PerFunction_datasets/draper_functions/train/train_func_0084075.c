extract_add_message (default_catalog_reader_ty *this,
                     char *msgctxt,
                     char *msgid,
                     lex_pos_ty *msgid_pos,
                     char *msgid_plural,
                     char *msgstr, size_t msgstr_len,
                     lex_pos_ty *msgstr_pos,
                     char *prev_msgctxt,
                     char *prev_msgid,
                     char *prev_msgid_plural,
                     bool force_fuzzy, bool obsolete)
{

  if (exclude != NULL && message_list_search (exclude, msgctxt, msgid) != NULL)
    goto discard;


  if (msgctxt == NULL && *msgid == '\0' && !xgettext_omit_header)
    {
      {
        const char *charsetstr = strstr (msgstr, "charset=");

        if (charsetstr != NULL)
          {
            size_t len;
            char *charset;

            charsetstr += strlen ("charset=");
            len = strcspn (charsetstr, " \t\n");
            charset = XNMALLOC (len + 1, char);
            memcpy (charset, charsetstr, len);
            charset[len] = '\0';

            if (header_charset != NULL)
              free (header_charset);
            header_charset = charset;
          }
      }

     discard:
      if (msgctxt != NULL)
        free (msgctxt);
      free (msgid);
      if (msgid_plural != NULL)
        free (msgid_plural);
      free (msgstr);
      if (prev_msgctxt != NULL)
        free (prev_msgctxt);
      if (prev_msgid != NULL)
        free (prev_msgid);
      if (prev_msgid_plural != NULL)
        free (prev_msgid_plural);
      return;
    }


  default_add_message (this, msgctxt, msgid, msgid_pos, msgid_plural,
                       msgstr, msgstr_len, msgstr_pos,
                       prev_msgctxt, prev_msgid, prev_msgid_plural,
                       force_fuzzy, obsolete);
}
